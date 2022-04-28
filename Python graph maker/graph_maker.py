"""
Module contains GUI code. The GUI is used as an interface to help the construction
of new graphs by showing a step by step image of the result
"""

import os
from time import time
from tkinter import (
    Tk,
    PhotoImage,
    Frame,
    Listbox,
    Label,
    Button,
    Radiobutton,
    Entry,
    StringVar,
    IntVar,
)
from tkinter import TOP, LEFT, RIGHT, YES, X, END
from tkinter import messagebox
from logo_downloader import download_logo
from config import DATA_DIR, LOGO_PATH, LOGO_URL
from parser_funcs import (
    format_data_to_txt,
    node_parser,
    format_data_to_gv,
    save_graph,
)

if not os.path.exists(DATA_DIR):
    os.mkdir(DATA_DIR)
if not os.path.exists(LOGO_PATH):
    download_logo(LOGO_URL, LOGO_PATH)

# Window Configurations
BG_COLOR = "#DFBF9F"
FONT = ("comicsans", 16)
FG_COLOR = "black"

BTN_BG_COLOR = "#C69358"

LABEL_BG_COLOR = "#DFBF9F"

ENTRY_BG_COLOR = "#FFD8AB"

# default name
DEFAULT_GRAPH_NAME = "Graph" + str(int(time()))


# Commands Functions
def select_item(event):
    """
    Function binded to the Listbox that saves the index of the selected item
    """

    global selected_item, index
    node_entry, connections_entry, weights_entry = (
        entries["Current Node"],
        entries["Connections"],
        entries["Weights"],
    )

    index = nodes_list.curselection()[0]
    selected_item = nodes_list.get(index).replace(", ", ",").split(" ")

    node, conn, weights = selected_item[0], selected_item[1], selected_item[2]

    conn = conn.replace("C[", "").replace("]", "").replace(",", " ")
    weights = weights.replace("W[", "").replace("]", "").replace(",", " ")

    node_entry.delete(0, END)
    connections_entry.delete(0, END)
    weights_entry.delete(0, END)

    node_entry.insert(END, node[1:])
    connections_entry.insert(END, conn)
    weights_entry.insert(END, weights)


def send_data(terminate=True):
    """
    Parses graph data and sends it to the graph contructor.
    """
    (*data,) = nodes_list.get(0, END)

    data = list(map(node_parser, data))

    graph_dot = format_data_to_gv(graph_name, data)
    graph_txt = format_data_to_txt(data)
    graph_path = save_graph(graph_name, graph_dot, graph_txt)

    if terminate is True:
        messagebox.showinfo("All Done!", "Your Graph was successfully created!")
        master.destroy()
    else:
        return graph_path


def add_node(index=END):
    """Adds item to Listbox

    Args:
        index (int, optional): Index of the selected item. Defaults to END.
    """
    node_entry, connections_entry, weights_entry = (
        entries["Current Node"],
        entries["Connections"],
        entries["Weights"],
    )

    if node_entry.get() == "" or connections_entry.get() == "":
        messagebox.showerror("Input Error", "Please fill all entry boxes!")
        return

    node_text = node_entry.get()

    connections = list(map(int, " ".join(connections_entry.get().split()).split(" ")))

    if weights_entry.get() == "":
        weights = [1 for _ in connections]
    else:
        weights = list(map(int, " ".join(weights_entry.get().split()).split(" ")))

    out = "N" + node_text + " C" + str(connections) + " W" + str(weights)

    nodes_list.insert(index, out)

    clear_input()

    new_graph_path = send_data(terminate=False)

    img = PhotoImage(file=new_graph_path + ".png")
    img_label.config(image=img)
    img_label.image = img


def update_selected():
    """
    Updates Selected item
    """
    nodes_list.delete(index)
    add_node(index)


def delete_selected():
    """
    Deletes selected item
    """
    nodes_list.delete(index)

    if nodes_list.size() == 0:
        img = PhotoImage(file=LOGO_PATH)
        img_label.config(image=img)
        img_label.image = img
    else:
        graph_path = send_data(terminate=False)
        img = PhotoImage(file=graph_path + ".png")
        img_label.config(image=img)
        img_label.image = img


def delete_all():
    """
    Deletes all items from the listbox
    """
    nodes_list.delete(0, END)
    clear_input()

    graph_path = os.path.join(DATA_DIR, graph_name)
    if os.path.exists(graph_path):
        os.system(f"rm {graph_path}/*")

    img = PhotoImage(file=LOGO_PATH)
    img_label.config(image=img)
    img_label.image = img


def clear_input():
    """
    Clears all input from entries
    """
    entries["Current Node"].delete(0, END)
    entries["Connections"].delete(0, END)
    entries["Weights"].delete(0, END)


def submit(win):
    """Submits the graph name and opens the master window.

    Args:
        win (TKinter window):
    """
    global graph_name

    if name_entry.get() == "":
        messagebox.showerror("Input Error", "Please fill all entry boxes!")
        return

    graph_name = name_entry.get().replace(" ", "").lower()
    if graph_name in ["graph", "digraph"]:
        graph_name += "_"

    win.destroy()
    master_window()


# Start GUI
def start():
    """
    First Window to apper, Asks user for Graph Name.
    """
    global name_entry

    win = Tk()
    win.resizable(False, False)
    win.title("Easy Graph Maker")
    win.config(background=BG_COLOR)

    logo = PhotoImage(file=LOGO_PATH)
    win.iconphoto(True, logo)

    # Creating rows
    row1 = Frame(win, bg=BG_COLOR)
    row2 = Frame(win, bg=BG_COLOR)

    # Creating Labels
    name_label = Label(
        row1,
        text="Graph Name",
        width=15,
        bg=BG_COLOR,
        fg=FG_COLOR,
        font=FONT,
    )

    # Creating entries
    name_entry = Entry(
        row1,
        textvariable=StringVar(row1, value=DEFAULT_GRAPH_NAME),
        background=ENTRY_BG_COLOR,
        foreground=FG_COLOR,
    )

    # Creating Buttons
    submit_button = Button(
        row2,
        text="Submit",
        width=12,
        command=lambda: submit(win),
        bg=BTN_BG_COLOR,
        fg=FG_COLOR,
        font=FONT,
    )
    quit_button = Button(
        row2,
        text="Quit",
        width=12,
        command=win.quit,
        bg=BTN_BG_COLOR,
        fg=FG_COLOR,
        font=FONT,
    )

    # Packing Widgets
    row1.pack(side=TOP, fill=X, padx=5, pady=5)
    row2.pack(side=TOP, fill=X, padx=5, pady=5)

    name_label.pack(side=LEFT)

    name_entry.pack(side=RIGHT, expand=YES, fill=X)

    quit_button.pack(side=LEFT, padx=5, pady=5)
    submit_button.pack(side=LEFT, padx=5, pady=5)

    win.mainloop()


# Main Tk Window
def master_window():
    """
    Main Window.
    """
    global master, entries, buttons, radios, nodes_list, row, img_label

    master = Tk()
    master.resizable(False, False)
    master.title("Easy Graph Maker")
    master.config(background=BG_COLOR)

    logo = PhotoImage(file=LOGO_PATH)
    master.iconphoto(True, logo)

    lab_fields = ["Current Node", "Connections", "Weights"]
    btn_fields = [
        ("Make Graph", send_data),
        ("Add", add_node),
        ("Update node", update_selected),
        ("Del node", delete_selected),
        ("Del All", delete_all),
        ("Clean", clear_input),
    ]
    radio_fields = ["Digraph", "Graph"]

    # Creating Labels and Entries
    entries = {}
    for field in lab_fields:
        row = Frame(master, bg=BG_COLOR)
        lab = Label(row, text=field, width=30, bg=BG_COLOR, fg=FG_COLOR, font=FONT)
        ent = Entry(row, bg=ENTRY_BG_COLOR, fg=FG_COLOR, font=FONT)
        row.pack(side=TOP, fill=X, padx=5, pady=5)
        lab.pack(side=LEFT)
        ent.pack(side=RIGHT, expand=YES, fill=X)
        entries[field] = ent

    # Creating Buttons
    buttons = {}
    row = Frame(master, bg=BG_COLOR)
    row.pack(side=TOP, fill=X, padx=5, pady=5)
    for field in btn_fields:
        btn = Button(
            row,
            text=field[0],
            command=field[1],
            width=10,
            bg=BTN_BG_COLOR,
            fg=FG_COLOR,
            font=FONT,
        )
        btn.pack(side=LEFT, padx=5, pady=5)
        buttons[field[0]] = btn

    # TODO: Upon clicking add_node, update_selected or delete_selected grab current radio button value and send it to send_data to appropriately update the graph.

    # Creating Radio Buttons
    radios = {}
    radio_var = IntVar()
    for index, field in enumerate(radio_fields):
        rad = Radiobutton(
            row,
            text=field,
            width=10,
            bg=BTN_BG_COLOR,
            fg=FG_COLOR,
            font=FONT,
            value=index,
            variable=radio_var,
        )
        rad.pack(side=LEFT, padx=5, pady=5)
        radios[field] = rad

    # Creating Listbox
    row = Frame(master, bg=BG_COLOR)
    row.pack(side=TOP, fill=X, padx=5, pady=5)
    nodes_list = Listbox(
        row,
        height=12,
        width=40,
        background=ENTRY_BG_COLOR,
        foreground=FG_COLOR,
        font=FONT,
    )
    nodes_list.pack(side=LEFT, fill=X, padx=5, pady=5)
    nodes_list.bind("<<ListboxSelect>>", select_item)

    # Creating Image Frame
    img = PhotoImage(file=LOGO_PATH)
    img_label = Label(row, image=img, bg=BG_COLOR)
    img_label.pack(side=LEFT, padx=200, pady=5)

    master.mainloop()


if __name__ == "__main__":
    start()

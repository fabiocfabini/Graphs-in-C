"""
Module Encharged of Parsing data to fit gv format requisites
"""

import os
from PIL import Image
from graphviz import Source
from config import DATA_DIR


def get_data_nodes(data):
    """
    Gets nodes from data
    """
    nodes = list(map(lambda x: x[0], data))

    conn_weights = list(map(lambda x: x[1], data))
    c_w = []
    for i in conn_weights:
        c_w.extend(i)
    conn = list(map(lambda x: x[0], c_w))

    nodes.extend(conn)

    nodes = list(range(max(nodes) + 1))

    return len(nodes), nodes, list(map(lambda x: x[0], data))


def format_data_to_txt(data):
    """
    formats graph data into easily data format for c program
    """

    node_count, total_nodes, nodes_with_connections = get_data_nodes(data)

    data = {node[0]: data[i][1] for i, node in enumerate(data)}
    graph_matrix = [
        [0 for _ in range(len(total_nodes))] for _ in range(len(total_nodes))
    ]
    for node in nodes_with_connections:
        for connection, weight in data[node]:
            graph_matrix[node][connection] = weight

    graph_txt = f"{node_count}\n"
    for row in graph_matrix:
        line = ""
        for col in row:
            line += f"{col} "
        graph_txt += line + "\n"

    return graph_txt[:-1]


def format_data_to_gv(graph_name, data, type):
    """format data to .gv file
    Args:
        NV (int): Number of Nodes in the graph
        graph_name (string): Name of the graph
        data (list): element format -> (int NV, list [(int connection, int weight)])
    """
    graph_dot = f"{type} {graph_name}" + "{"
    sep = " "
    if type == "Digraph": sep += "->"
    else: sep += "--"

    for node_data in data:
        line = ""
        for node_connection, weight in node_data[1]:
            line += f"\n\t{node_data[0]} {sep} {node_connection} [label = {weight}]"
        graph_dot += line

    graph_dot += "\n}"

    return graph_dot


def save_graph(graph_name, graph_dot, graph_txt, view=False):
    """
    Saves graph image to the DATA_DIR
    """
    graph_path = os.path.join(DATA_DIR, graph_name)

    if os.path.exists(graph_path):
        os.system(f"rm {graph_path}/*")
    else:
        os.mkdir(graph_path)

    graph_path = os.path.join(graph_path, graph_name)
    src = Source(graph_dot, filename=graph_path, format="png", engine="circo")
    src.render(view=view)

    with Image.open(graph_path + ".png") as img:
        img.resize((300, 300))

    with open(graph_path + ".txt", "w", encoding="utf-8") as txt:
        txt.write(graph_txt)

    return graph_path


def node_parser(content):
    """formats node date to simplify later operations

    Args:
        content (strign): str ouput from GUI module in the format :'N1 C[1, 2, 3] W[1, 2, 3]'

    Returns:
        tuple: parsed node data of the format: (1, [(1,1),(2,2),(3,3)])
    """
    content = content.replace(", ", ",").split(" ")
    node, conn, weight = content[0], content[1], content[2]

    node = int(node[1:])

    conn = map(int, conn.replace("C[", "").replace("]", "").split(","))
    weight = map(int, weight.replace("W[", "").replace("]", "").split(","))

    node_data = tuple(zip(conn, weight))

    return (node, node_data)


if __name__ == "__main__":
    SOURCE = """
    Graph dijkstra{
        0 -- 1 [label = 9]
        0 -- 2 [label = 2]
        0 -- 3 [label = 1]
        0 -- 4 [label = 3]
        1 -- 4 [label = 9]
        1 -- 3 [label = 1]
        1 -- 2 [label = 2]
        1 -- 1 [label = 3]
        2 -- 1 [label = 1]
        2 -- 2 [label = 1]
        3 -- 3 [label = 5]
        3 -- 2 [label = 1]
        4 -- 4 [label = 1]
        4 -- 3 [label = 1]
        4 -- 2 [label = 1]
        4 -- 1 [label = 1]
        4 -- 0 [label = 1]
    }
    """
    SRC = Source(SOURCE, filename="test", format="png", engine="circo")
    SRC.render(view=False)

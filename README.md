# Graph Algorithms in C 

This repository will contain some of the most popular graph algorithms. It also contains a simple python program that allows for an easier configuration of the graphs. 

## Python Graph Maker

This is the directory that contains the python program that allows for the creation of graphs. To run the program, simply type the following in the terminal:

```pip install -r requirements.txt```

Then, type the following in the terminal:

```python graph_maker.py```

After the program has been run, you will be prompted to enter the name of the file that you want to create. 

A second page will appear prompting you to enter the current node, it's connections and the corresponding weights.

An image of the graph will be created during the process to show the current state of the graph.

Upon completion, a folder will be created with the name of the file you entered. This folder will contain the following files:
- <entered_name>.txt - This is the file that contains the graph information in a easily accessible format for c.
- <entered_name>.png - This is the file that contains the graph image.
- <entered_name>.dot - This is the file that contains the graph in the dot format.

## C code

In this directory, you will find the C code for the algorithms as well as the C program that fetchs the data from the graph files.

To compile and run the C code, type the following in the terminal:

```make && bin/main```

The header files are located in the directory:

```C code/includes/```

## More Information

If you have any questions or criticisms, feel free to contact me at:

@[instagram](https://www.instagram.com/fabiocfabini/)cd

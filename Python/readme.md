for graph.py here's some example usage. 

```python 

>>> connections = [('A', 'B'), ('B', 'C'), ('B', 'D'),
                   ('C', 'D'), ('E', 'F'), ('F', 'C')]
>>> g = Graph(connections, directed=True)
>>> pprint(g._graph)
{'A': {'B'},
 'B': {'D', 'C'},
 'C': {'D'},
 'E': {'F'},
 'F': {'C'}}

>>> g = Graph(connections)  # undirected
>>> pprint(g._graph)
{'A': {'B'},
 'B': {'D', 'A', 'C'},
 'C': {'D', 'F', 'B'},
 'D': {'C', 'B'},
 'E': {'F'},
 'F': {'E', 'C'}}

>>> g.add('E', 'D')
>>> pprint(g._graph)
{'A': {'B'},
 'B': {'D', 'A', 'C'},
 'C': {'D', 'F', 'B'},
 'D': {'C', 'E', 'B'},
 'E': {'D', 'F'},
 'F': {'E', 'C'}}

>>> g.remove('A')
>>> pprint(g._graph)
{'B': {'D', 'C'},
 'C': {'D', 'F', 'B'},
 'D': {'C', 'E', 'B'},
 'E': {'D', 'F'},
 'F': {'E', 'C'}}

>>> g.add('G', 'B')
>>> pprint(g._graph)
{'B': {'D', 'G', 'C'},
 'C': {'D', 'F', 'B'},
 'D': {'C', 'E', 'B'},
 'E': {'D', 'F'},
 'F': {'E', 'C'},
 'G': {'B'}}

>>> g.find_path('G', 'E')
['G', 'B', 'D', 'C', 'F', 'E']

```

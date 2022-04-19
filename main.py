from grammar import *
from parse import *
from parser import *

with open("/Users/cindyhainz/Documents/OTH/06_Semester/DNLP/02_Uebung/03_Uebung/grammar/data/telescope.srgs", "r") as f:
    lines = f.readlines()
    print("\n".join(lines))
    gr = Grammar(lines)
    Grammar.is_CNF(gr)
    
sentence = "my saw saw her saw with I"
tokens = sentence.split(" ")

is_in_language(tokens, gr)


#print(example_telescope_parse().to_dot())

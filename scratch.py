import grammar
import parse
import parser

with open("../data/telescope.srgs", "r") as f:
    lines = f.readlines()
    print("\n".join(lines))
    gr = grammar.Grammar(lines)
print(gr)

print(parser.example_telescope_parse().to_dot())

sentence = "I saw the duck with a telescope"
tokens = sentence.split(" ")

parser.is_in_language(tokens, gr)

parsing_results = parse(tokens, gr)  # oups this fails at the moment...
# one of the parsing results  should yield the same result as the example from above

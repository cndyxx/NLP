import re


class Symbol:
    """symbols of the grammar"""

    terminal: bool
    symbol: str

    def __init__(self, symbol: str):
        self.terminal = not symbol.startswith("$")
        self.symbol = symbol if self.terminal else symbol[1:]

    def __repr__(self):
        return ("" if self.terminal else "$") + self.symbol

    def __eq__(self, other):
        return self.symbol == other.symbol and self.terminal == other.terminal


class GrammarRule:
    """
    simple sequence rule.
    We don't support anything more complex;
    alternatives will have to be split into multiple sub-rules """

    lhs: Symbol
    rhs: list  # it's a list of Symbols

    def __init__(self, lhs: Symbol, rhs: list):
        self.lhs, self.rhs = lhs, rhs

    def __eq__(self, other):
        return self.lhs == other.lhs and self.rhs == other.rhs

    def __repr__(self):
        return str(self.lhs) + " = " + " ".join([str(s) for s in self.rhs]) + ";"


class Grammar:
    language: str
    start_symbol: Symbol
    rules = []  # list of GrammarRules
    symbols = {}  # map from strings to symbols

    """initialize a new grammar from a srgs grammar file"""
    def __init__(self, lines, grammar_format="SRGS"):  # FIXME: maybe implement JSGF import in the future
        assert grammar_format == "SRGS", "illegal format descriptor: {}".format(grammar_format)
        lines = [re.sub("//.*$", "", line) for line in lines]  # remove comment lines
        lines = [line.strip() for line in lines if not re.match(r"^ *$", line)]  # remove empty lines
        assert lines.pop(0).lower() == "#abnf v1.0 utf-8;", "maybe something is wrong with header?"
        lang = re.match(r"language\s+(\S*)\s*;", lines.pop(0).lower())
        assert lang and len(lang.groups()) == 1, "cannot find correct language tag: {}".format(lang)
        self.language = lang.group(0)
        for line in lines:
            match = re.match(r"((?:public)?)\s*(\$\S+)\s*=\s*(.*)\s*;", line)
            assert match and len(match.groups()) == 3, "cannot parse line {}".format(line)
            is_public = match.group(1) != ""
            lhs = self.get_symbol(match.group(2))
            rhs = [self.get_symbol(s) for s in re.split(r"\s+", match.group(3))]
            self.rules.append(GrammarRule(lhs, rhs))
            if is_public:
                self.start_symbol = lhs

    def get_symbol(self, symbol: str):
        if symbol not in self.symbols:
            self.symbols[symbol] = Symbol(symbol)
        return self.symbols[symbol]

    def __repr__(self):
        return "#ABNF V1.0 utf-8\n" + \
               "language " + self.language + "\n" + \
               "\n".join([str(r) if r.lhs != self.start_symbol else "public " + str(r) for r in self.rules])

    def is_CNF(self): #is the given grammar in CNF? -> return True or False
        isCNF = True #returnvalue
        for rule in self.rules: #check all grammar rules if they are in CNF
            #on the right side has to be exactly one terminal symbol
            #or exactly two non-terminal symbols
            #if not:
            if not((len(rule.rhs) == 1 and rule.rhs[0].terminal == True) or (len(rule.rhs) == 2 and rule.rhs[0].terminal == False and rule.rhs[1].terminal == False)): 
                isCNF = False
                break #if one grammarrule is false the rest doesn't have to be looked at because the grammar isn't in CNF
        if isCNF == False:
            print("The Grammar is not in CNF")
            return False
        else:
            print("The Grammar is in CNF")
            return True    
        


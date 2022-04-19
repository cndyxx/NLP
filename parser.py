from grammar import *
from parse import *
import numpy as np

#def in_list(nonterminal: list, symbol:Symbol) -> bool: #extra function to check, if the symbol is in the given list of symbols
    #for i in range(0,len(nonterminal)): #check for every symbol in list, if symbol is the same        
        #if nonterminal[i]==symbol:
            #return True
    #return False

def in_list(nonterminal: list, symbol:Symbol) -> int: #extra function to check, if the symbol is in the given list of symbols
    quantity = 0
    for i in range(0,len(nonterminal)): #check for every symbol in list, if symbol is the same        
        if nonterminal[i]==symbol:
            quantity +=1
    return quantity
              

def is_in_language(words: list, grammar: Grammar) -> bool:
    # TODO: in the beginning, this is your job.
    # it is easier to start out with a parser that merely
    # checks if the sentence is in the language at all (without returning
    # the derivations).
    # eventually, once you have implemented parse() below,
    # you can simply write
    # "return len(parse(words, grammar)) > 0"

    
    if Grammar.is_CNF(grammar): #CYK just works if the grammar is in CNF
        n = len(words)
        table = np.empty((n, n),list) #create 2D list over qantitiy of words

        i = 0 #to know which word is currently looked at
        for word in words: 
            temp_list=[]
            for rule in grammar.rules: #check for every grammar rule:
                if len(rule.rhs) == 1 and rule.rhs[0].symbol==word: #is the current word on the right side
                    temp_list.append(rule.lhs) #if so: put left side into temporary list
                
            table[0][i]=temp_list #after all grammar rules are looked at for the current word: put the temporary list into the first row of table at index i  
            i+=1

        #print(table)
        for j in range(1,n): #Row to write in
            for i in range(0,n-j): #Column to write in
                temp_list=[]
                for k in range(0,j): #Range to look at all combinations for the entry to table[j][i]
                    #print(j,i,k)
                    #print(table[k][i])
                    #print(table[j-k-1][i+k+1])
                    for rule in grammar.rules: #Look at all grammar rules for the combination of the non-terminals looked at
                        #the rule has to have two nonterminals on the right side
                        #and the two entries looked at from the table should not be empty
                        #and the first nonterminal should be in the list of the first entry
                        #and the second nonterminal should be in the list of the second entry
                        if len(rule.rhs) == 2 and table[k][i] != None and table[j-k-1][i+k+1] != None: #and in_list(table[k][i],rule.rhs[0])>0 and in_list(table[j-k-1][i+k+1],rule.rhs[1])>0:
                            first = in_list(table[k][i],rule.rhs[0])
                            second = in_list(table[j-k-1][i+k+1],rule.rhs[1])
                            if first > 0 and second > 0:
                                if first >= second:
                                    for a in range(0,first):
                                        temp_list.append(rule.lhs) #add left side of rule to temporary list
                                elif second > first:
                                    for a in range(0,second):
                                        temp_list.append(rule.lhs) #add left side of rule to temporary list
                            #print("true")
                            #print(temp_list)                            
                table[j][i]=temp_list #after all grammar rules are looked at for all Range combinations: put the temporary list into the j row of table at index i  
                #print(table[j][i])
                #print(temp_list) 
                    
        print(table)
        if in_list(table[n-1][0],grammar.start_symbol): #if the startsymbol is in the list of the last table entry: the sentence is in the language
            print("Sentence is in the language")
            return True
        else:
            print("Sentence is not in the language")
            return False



def parse(words: list, grammar: Grammar) -> list:
    """
    parses the list of words with grammar and returns the (possibly empty) list
    of possible parses. The ordering of possible parses is arbitrary.
    returns a list of ParseTree
    """
    raise NotImplementedError  # TODO: this is your job.
    return []  # not much better than the exception because we promise above to return all parses...


def example_telescope_parse():
    return \
        ParseTree(Symbol("$S"),
                  [ParseNode(Symbol("$NP"),
                             [ParseNode(Symbol("I"))]),
                   ParseNode(Symbol("$VP"),
                             [ParseNode(Symbol("$VP"),
                                        [ParseNode(Symbol("$V"),
                                                   [ParseNode(Symbol("saw"))]),
                                         ParseNode(Symbol("$NP"),
                                                   [ParseNode(Symbol("$Det"),
                                                              [ParseNode(Symbol("the"))]),
                                                    ParseNode(Symbol("$N"),
                                                              [ParseNode(Symbol("duck"))])])]),
                              ParseNode(Symbol("$PP"),
                                        [ParseNode(Symbol("$P"),
                                                   [ParseNode(Symbol("with"))]),
                                         ParseNode(Symbol("$NP"),
                                                   [ParseNode(Symbol("$Det"),
                                                              [ParseNode(Symbol("a"))]),
                                                    ParseNode(Symbol("$N"),
                                                              [ParseNode(Symbol("telescope"))])])])])])

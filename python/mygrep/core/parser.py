from dataclasses import dataclass

from .automaton import EPSILON, ALPHABET


@dataclass
class AST:
    def __init__(self, tag, *args):
        self.tag: str = tag
        self.childs: list = args

    def __repr__(self):
        return f"AST({self.tag}, {self.childs})"

    def print(self, indent=0):
        """
        Prints a pretty AST representation
        """
        print("  " * indent, self.tag)
        if self.tag == "CharGroup":
            print("  " * (indent + 1), "".join(self.childs))
        else:
            for child in self.childs:
                child.print(indent + 1)


def parse(regex: str) -> AST:
    """
    Constructs an AST from a regex in postfixe form
    """
    stack = []
    for c in regex:
        if c == "@":
            right, left = stack.pop(), stack.pop()
            stack.append(AST("Concat", left, right))
        elif c == "|":
            right, left = stack.pop(), stack.pop()
            stack.append(AST("Union", left, right))
        elif c == '*':
            stack.append(AST("Star", stack.pop()))
        elif c == '?':
            stack.append(AST("Union", EPSILON, stack.pop()))
        elif c == '.':
            stack.append(AST("CharGroup", *ALPHABET))
        else:
            stack.append(AST("CharGroup", c))
    return stack.pop()

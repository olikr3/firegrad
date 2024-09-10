"""
a scalar valued type
"""
class Scalar:

    def __init__(self, parents=()):
        self.parents = parents

    def params(self):
        self.params = []

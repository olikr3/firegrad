
class Tensor:
    """ Represents a wrapper around a np.ndarray """

    def __init__(self, data, _children=(), _ops=()):
        assert type(data) == np.ndarray
        self.data = data
        self.grad = 0
        #required for autograd:
        self._backward = lambda: None
        self._prev = set(children)
        self._ops = ops

    def __add__(self, other):
        assert isinstance(other, Tensor)
        result = Tensor(self.data + other.data)

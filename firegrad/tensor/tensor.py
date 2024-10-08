import numpy as np

class Tensor:
    """ Represents a wrapper around a np.ndarray """

    def __init__(self, data, _children=(), _ops=()):
        assert type(data) == np.ndarray
        self.data = data
        self.grad = 0
        #required for autograd:
        self._backward = lambda: None
        self._prev = set(_children)
        self._ops = _ops

    def __add__(self, other: 'Tensor', alpha=1) -> 'Tensor':
        """
        returns a new tensor: result = self + alpha*other
        """
        assert isinstance(other, Tensor)
        assert self.data.shape == other.data.shape
        result = Tensor(self.data + (alpha*other.data))
        
        return result
    
    def __sub__(self, other: 'Tensor', alpha=1) -> 'Tensor':
        """
        returns a new tensor: result = self - alpha*other
        """
        assert isinstance(other, Tensor)
        assert self.data.shape == other.data.shape
        return Tensor(self.data + (-1 * alpha * other.data))


    def __mul__(self, other: 'Tensor') -> 'Tensor':
        assert isinstance(other, Tensor)
        result = Tensor(self.data * other.data)
        
        return result

    def __neg__(self, other: 'Tensor') -> 'Tensor':
        result = Tensor(-1 * self.data)
        return result

    def __str__(self):
        return f"firegrad.tensor{self.data}, {self.grad}"


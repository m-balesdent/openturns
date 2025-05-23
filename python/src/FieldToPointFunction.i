// SWIG file FieldToPointFunction.i

%{
#include "openturns/FieldToPointFunction.hxx"
#include "openturns/PythonFieldToPointFunction.hxx"

namespace OT {

  template <>
  struct traitsPythonType< OT::FieldToPointFunction >
  {
    typedef _PyObject_ Type;
  };

  template <>
  inline
  bool
  canConvert< _PyObject_, OT::FieldToPointFunction >(PyObject * pyObj)
  {
    void * ptr = 0;
    if (SWIG_IsOK(SWIG_ConvertPtr(pyObj, &ptr, SWIGTYPE_p_OT__FieldToPointFunction, SWIG_POINTER_NO_NULL))) {
      OT::FieldToPointFunction * p_nmf = reinterpret_cast< OT::FieldToPointFunction * >(ptr);
      return p_nmf != NULL;
    } else if (SWIG_IsOK(SWIG_ConvertPtr( pyObj, &ptr, SWIGTYPE_p_OT__FieldToPointFunctionImplementation, 0 ))) {
      OT::FieldToPointFunctionImplementation * p_impl = reinterpret_cast< OT::FieldToPointFunctionImplementation * >(ptr);
      return p_impl != NULL;
    } else {
      return PyCallable_Check( pyObj );
    }
  }

  template <>
  inline
  OT::FieldToPointFunction
  convert< _PyObject_, OT::FieldToPointFunction >(PyObject * pyObj)
  {
    void * ptr = 0;
    if (SWIG_IsOK(SWIG_ConvertPtr(pyObj, &ptr, SWIGTYPE_p_OT__FieldToPointFunction, SWIG_POINTER_NO_NULL))) {
      OT::FieldToPointFunction * p_nmf = reinterpret_cast< OT::FieldToPointFunction * >( ptr );
      return *p_nmf;
    } else if (SWIG_IsOK(SWIG_ConvertPtr( pyObj, &ptr, SWIGTYPE_p_OT__FieldToPointFunctionImplementation, 0))) {
      OT::FieldToPointFunctionImplementation * p_impl = reinterpret_cast< OT::FieldToPointFunctionImplementation * >(ptr);
      return *p_impl;
    } else if (!PyCallable_Check(pyObj)) {
      throw OT::InvalidArgumentException(HERE) << "Argument is not a callable object (function or class) - can not be convertible to a FieldToPointFunction";
    }
    OT::FieldToPointFunction pythonFunction(new OT::PythonFieldToPointFunction(pyObj));
    return pythonFunction;
  }

} /* namespace OT */

%}

%include FieldToPointFunction_doc.i

OTTypedInterfaceObjectHelper(FieldToPointFunction)

%include openturns/FieldToPointFunction.hxx

namespace OT { 
%extend FieldToPointFunction {

FieldToPointFunction(PyObject * pyObj)
{
  void * ptr = 0;
  if (SWIG_IsOK(SWIG_ConvertPtr(pyObj, &ptr, SWIGTYPE_p_OT__Object, 0)))
  {
    throw OT::InvalidArgumentException(HERE) << "Argument should be a pure python object";
  }
  return new OT::FieldToPointFunction(OT::convert<OT::_PyObject_, OT::FieldToPointFunction>(pyObj));
}

FieldToPointFunction(const FieldToPointFunction & other) { return new OT::FieldToPointFunction( other ); }

}}

%pythoncode %{

class OpenTURNSPythonFieldToPointFunction:
    r"""
    Override FieldToPointFunction from Python.

    Parameters
    ----------
    inputMesh : :class:`~openturns.Mesh`
        The input mesh.
    inputDim : positive int
        Dimension of the input field values :math:`\inputDim`.
    outputDim : positive int
        Dimension of the output vector d'.

    Notes
    -----
    A OpenTURNSPythonFieldToPointFunction function acts on fields to produce points:

    .. math::

        f: \left| \begin{array}{rcl}
                    \cM_N \times (\Rset^\inputDim)^N & \rightarrow &\Rset^{d'} \\
                    F & \mapsto & \vect{v}'
                  \end{array} \right.

    with  :math:`\cM_N` a mesh of :math:`\cD \subset \Rset^n`.

    A field is represented by a collection :math:`(\vect{t}_i, \vect{v}_i)_{1 \leq i \leq N}`
    of elements of :math:`\cM_N \times (\Rset^d)^N` where :math:`\vect{t}_i` is a vertex of :math:`\cM_N` and
    :math:`\vect{v}_i` the associated value in :math:`\Rset^\inputDim`.

    At least, you have to overload the function:
        _exec(X): a single evaluation, where X is a :class:`~openturns.Field`. It returns
        a :class:`~openturns.Point`.

    Examples
    --------    
    For example, we create the function that maps a field to the mean value of its values.
    
    >>> import openturns as ot
    >>> mesh = ot.Mesh(1)
    >>> class FUNC(ot.OpenTURNSPythonFieldToPointFunction):
    ...    def __init__(self):
    ...         # first argument:
    ...         super(FUNC, self).__init__(mesh, 2, 2)
    ...         self.setInputDescription(['R', 'S'])
    ...         self.setOutputDescription(['T', 'U'])
    ...    def _exec(self, X):
    ...         Y = ot.Sample(X).computeMean()
    ...         return Y
    >>> F = FUNC()
    """
    def __init__(self, inputMesh, inputDim, outputDim):
        if not isinstance(inputMesh, openturns.geom.Mesh):
            raise TypeError('inputMesh argument is not a Mesh.')
        self.__inputMesh = inputMesh
        try:
            self.__inputDim = int(inputDim)
        except:
            raise TypeError('inputDim argument is not an integer.')
        try:
            self.__outputDim = int(outputDim)
        except:
            raise TypeError('outputDim argument is not an integer.')
        self.__descIn = ['x' + str(i) for i in range(inputDim)]
        self.__descOut = ['y' + str(i) for i in range(outputDim)]

    def setInputDescription(self, descIn):
        """
        Accessor to the description of the input field values.

        Parameters
        ----------
        descIn : sequence of str
            The description of the input field values.    
        """
        if (len(descIn) != self.__inputDim):
            raise ValueError('Input description size does NOT match input dimension')
        self.__descIn = descIn

    def getInputDescription(self):
        """
        Accessor to the description of the input field values.

        Returns
        -------
        descIn : sequence of str
            The description of the input field values.    
        """
        return self.__descIn

    def setOutputDescription(self, descOut):
        """
        Accessor to the description of the output values of the function.

        Parameters
        ----------
        descOut : sequence of str
            The description of the output values of the function.    
        """
        if (len(descOut) != self.__outputDim):
            raise ValueError('Output description size does NOT match output dimension')
        self.__descOut = descOut

    def getOutputDescription(self):
        """
        Accessor to the description of the output values of the function.

        Returns
        -------
        descOut : sequence of str
            The description of the output values of the function.    
        """
        return self.__descOut

    def getInputDimension(self):
        r"""
        Accessor to the dimension of the input field values.

        Returns
        -------
        inputFieldDim : int
            The dimension of the input field values  :math:`\inputDim`.   
        """
        return self.__inputDim

    def getOutputDimension(self):
        r"""
        Accessor to the dimension of the output values of the function.

        Returns
        -------
        outputDim : int
            The dimension of the output values of the function :math:`d'`.    
        """
        return self.__outputDim

    def getInputMesh(self):
        """
        Accessor to the mesh of the input field.

        Returns
        -------
        inputMesh : :class:`~openturns.Mesh`
            The mesh of the input field.  
        """
        return self.__inputMesh

    def __str__(self):
        return f"OpenTURNSPythonFieldToPointFunction( {self.__descIn} #{self.__inputDim} ) -> {self.__descOut} #{self.__outputDim}"

    def __repr__(self):
        return self.__str__()

    def __call__(self, X):
        Y = None
        if isinstance(X, ProcessSample):
            Y = self._exec_sample(X)
        else:
            Y = self._exec(X)
        return Y

    def _exec(self, X):
        raise RuntimeError('You must define a method _exec(X) -> Y, where X is a Field object and Y a Point object')

    def _exec_sample(self, X):
        res = list()
        for i in range(len(X)):
            res.append(self._exec(X[i]))
        return res

    def _exec_point_on_exec_sample(self, X):
        """Implement exec from exec_sample."""
        return self._exec_sample([X])[0]

class PythonFieldToPointFunction(FieldToPointFunction):
    r"""
    Override FieldToPointFunction from Python.

    Parameters
    ----------
    inputMesh : :class:`~openturns.Mesh`
        The input mesh
    inputDim : positive int
        Dimension of the input field values d
    outputDim : positive int
        Dimension of the output vector d'
    func : a callable python object
        called on a :class:`~openturns.Field` object.
        Returns a :class:`~openturns.Field`.
        Default is None.

    Notes
    -----
    A PythonFieldToPointFunction acts on fields to produce points:

    .. math::

        f: \left| \begin{array}{rcl}
                    \cM_N \times (\Rset^\inputDim)^N & \rightarrow &\Rset^{d'} \\
                    F & \mapsto & \vect{v}'
                  \end{array} \right.

    with  :math:`\cM_N` a mesh of :math:`\cD \subset \Rset^n`.

    Examples
    --------
    For example, we create the function that maps a field to the mean value of its values. The values of the input field are of dimension :math:`d = 2` and the output value of the function is also of dimension :math:`d' = 2`.
    
    >>> import openturns as ot
    >>> mesh = ot.Mesh(1)
    >>> def myPyFunc(X):
    ...     Y = ot.Sample(X).computeMean()
    ...     return Y
    >>> inputDim = 2
    >>> outputDim = 2
    >>> myFunc = ot.PythonFieldToPointFunction(mesh, inputDim, outputDim, myPyFunc)
    """
    def __new__(self, inputMesh, inputDim, outputDim, func=None):
        if func is None:
            raise RuntimeError('func not provided.')
        instance = OpenTURNSPythonFieldToPointFunction(inputMesh, inputDim, outputDim)
        if func is not None:
            if not callable(func):
                raise RuntimeError('func argument is not callable.')
            instance._exec = func
        return FieldToPointFunction(instance)


%}

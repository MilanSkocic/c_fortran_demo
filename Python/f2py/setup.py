import platform
from setuptools import find_packages
import numpy
from setuptools import Extension, setup
from setuptools.command.build_ext import build_ext


class CustomBuildExt( build_ext ):
    r"""Custom class for building extension."""
    def build_extensions(self):
        r"""Custom building function for mingw32 on windows"""
        c = self.compiler.compiler_type
        if (c == "mingw32") and (platform.system() == "Windows"):
           for e in self.extensions:
               e.extra_link_args += ["-static"]
        build_ext.build_extensions(self)


fib_c_ext = Extension(name="example.fib_c",
                      sources=["./example/_fib.c", "./example/fib.c"],
                      include_dirs=[numpy.get_include()],
                      define_macros=[('NPY_NO_DEPRECATED_API', 'NPY_1_7_API_VERSION')])

fib_fortran_ext = Extension(name="example.fib_f90",
                            sources=["./example/fib.f90"],
                            include_dirs=[numpy.get_include()],
                            define_macros=[('NPY_NO_DEPRECATED_API', 'NPY_1_7_API_VERSION')])

setup(
    name="C and Fortran Extension Demo",
    version="1.0",
    packages=find_packages(),
    include_package_data=True,
    cmdclass = {'build_ext': CustomBuildExt},
    ext_modules=[fib_c_ext]
)

import os, sys

from distutils.core import setup, Extension
from distutils import sysconfig

cpp_args = ['-std=c++11', '-stdlib=libc++', '-mmacosx-version-min=10.7']

sfc_module = Extension(
    'alpyao', sources=['module.cpp', 'FakeAlpao.cpp', 'AlpaoDM.cpp'],
    include_dirs=['pybind11/include', 'C:/Program Files/Alpao/SDK/Include'],
    language='c++',
    extra_compile_args=cpp_args,
	library_dirs = ['C:/Program Files/Alpao/SDK/Lib/x64'],
	libraries=['ASDK',]
)

setup(
    name='alpyao',
    version='0.1',
    description='Python package with superfastcode2 C++ extension (PyBind11)',
    ext_modules=[sfc_module],
)
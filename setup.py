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
    description='Alpyao is a pybind11 wrapper for the Alpao SDK3.',
    ext_modules=[sfc_module],
	author='Sebastiaan Y. Haffert',
	author_email='shaffert@email.arizona.edu',
	url='https://github.com/syhaffert/alpyao',
)
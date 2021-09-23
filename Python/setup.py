from setuptools import setup, find_packages
import codecs
import os

here = os.path.abspath(os.path.dirname(__file__))

with codecs.open(os.path.join(here, "./README.md"), encoding="utf-8") as fh:
    long_description = "\n" + fh.read()

VERSION = '1.0.6'
DESCRIPTION = 'SimpleEncrypt is a Cross-Language Encryption Library'

# Setting up
setup(
    name="simpleencrypt",
    version=VERSION,
    author="Shreyas Nayak",
    author_email="<shreyasnayak21@gmail.com>",
    description=DESCRIPTION,
    long_description_content_type="text/markdown",
    long_description=long_description,
    packages=find_packages(),
    install_requires=[],
    keywords=['Encryption', 'Cross-Language Encryption'],
    classifiers=[
        "Development Status :: 4 - Beta",
        "Intended Audience :: Developers",
        "Programming Language :: Python :: 3",
        "Operating System :: Unix",
    ]
)

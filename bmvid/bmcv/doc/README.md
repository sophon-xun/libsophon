This is the document repo of BMCV.


## Prerequisites

install **sphinx** texlive-xetex texlive-latex-recommended

```shell
pip install sphinx sphinx-autobuild sphinx_rtd_theme rst2pdf
```

## Get Fandol font for linux system

* [Fandol](https://ctan.org/pkg/fandol) - Four basic fonts for Chinese typesetting

Download the fandol package from the aboved website(wget http://mirrors.ctan.org/fonts/fandol.zip) and unzip it.

Copy the fold named fandol to /usr/share/fonts or ${HOME}/.fonts.

If fandol exists in /usr/share/fonts, we can ignore this step.


## Compilation

```shell
## if you want html
make web # build document to static html files

python3 -m http.server --directory build/html
# open http://localhost:8000 in browser

or directly open build/html/index.html
 

## if you want pdf
make pdf
# the pdf is in build/latex/
```

## Testing

TODO

## Deployment

TODO

## Built With

* [Sphinx](http://www.sphinx-doc.org) - Document auto generate tool  
* [Latex](https://www.latex-project.org/) - High-quality typesetting system 

## License

This project is licensed under the MIT License - see the LICENSE file for details

## Acknowledgments

### Computing the longest common prefix array based on the Burrows–Wheeler transform

Bioinformatics student project.

[http://www.fer.unizg.hr/predmet/bio](http://www.fer.unizg.hr/predmet/bio)

## Installing

Clone this repo from github:

```
git clone --recursive https://github.com/giavjeko/bio.git
```

Once in the repo directory:
(replace myusergroup with your user group)
```
sudo ./measure --setup -g myusergroup --perm 775
make
```

## Testing

To run tests on all modules run ```make test```

## Running

Run ```./lcp [input_file_path] [output_file_path]```
Test input and correct output files are located in ```files``` directory

### Analysis

To run automated algorythm analysis run
```
./analysis.sh
```

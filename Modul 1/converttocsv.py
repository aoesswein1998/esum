import pandas as pd

read_file = pd.read_csv(r'putty.log', sep=".00", keep_default_na=False, names=['x','y','z','remove'])
read_file.drop('remove', axis=1, inplace=True)
read_file.to_csv(r'putty.csv', index=None)
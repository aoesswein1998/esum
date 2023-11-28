import pandas as pd

read_file = pd.read_csv(r'F:\_Uni\ESUM\Modul 1\Messung\420rpm.txt', sep=",", keep_default_na=False, names=['si','pga','x','y','z','time'])
#read_file.drop('remove', axis=1, inplace=True)
read_file.to_csv(r'420rpm.csv', index=None)
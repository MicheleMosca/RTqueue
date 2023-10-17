#!/usr/bin/python3

import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
import sys

filename = sys.argv[1]

df = pd.read_csv(filename, sep=' ')
df.loc[df['Read'] == 0.0, 'Thread'] = "read_thread0"
df.loc[df['Read'] == 1.0, 'Thread'] = "read_thread1"

plt.figure(figsize=(15,10))
sns.barplot(data=df, x = "Iter", y="Time", hue="Thread", errorbar=None)
plt.title(filename.split('_')[0])

print("Statistics Metrics Writer0 (Write)")
print(df[df['Thread'] == 'writer0']['Time'].describe())
print()

print("Statistics Metrics Writer0 (Read)")
print(df[df['Thread'] == 'read_thread0']['Time'].describe())
print()

print("Statistics Metrics Writer1 (Write)")
print(df[df['Thread'] == 'writer1']['Time'].describe())
print()

print("Statistics Metrics Writer1 (Read)")
print(df[df['Thread'] == 'read_thread1']['Time'].describe())
print()

#plt.show()
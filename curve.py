import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("equity_curve.csv")

plt.plot(df["Date"],df["Portfolio"])
plt.ylabel("Portfolio Value")
plt.xlabel("Date")
plt.show()
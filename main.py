import pandas as pd # type: ignore

#load SPY data
df = pd.read_csv("SPY.csv")

#create moving averages
df["short_moving_average"] = df["adjusted_close"].rolling(10).mean()
df["long_moving_average"] = df["adjusted_close"].rolling(50).mean()

#function determing signal
def determineSignal(MA10, MA50):
    if MA10 > MA50:
        return "BUY"
    elif MA10 < MA50:
        return "SELL"
    else:
        return "HOLD"

#apply determineSignal to each row
df["signal"] = df.apply(lambda row: determineSignal(row["short_moving_average"],row["long_moving_average"]),axis=1)

#keep dataframe minimal for actual simulation
df = df.drop(["open","high","low","close","volume","change_percent","avg_vol_20d","short_moving_average","long_moving_average"], axis=1)
df = df.rename(columns={"adjusted_close":"price"})


df.to_csv("output.csv",index=False)



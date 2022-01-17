using System;
using System.Runtime.InteropServices;

public class LibWrapper
{
    [DllImport("ChessAnalytics")]
    public static extern IntPtr createMlpModel(int[] npl, int nplSize);

    [DllImport("ChessAnalytics")]
    public static extern void destroyMlpModel(IntPtr model);

    [DllImport("ChessAnalytics")]
    public static extern void destroyMlpResult(IntPtr result);

    [DllImport("ChessAnalytics")]
    public static extern IntPtr predictMlpModelRegression(IntPtr model, double[] sampleInputs, int inputDim);

    [DllImport("ChessAnalytics")]
    public static extern void trainMlpModelRegression(IntPtr model, double[] samplesInputs,
        double[] samplesExpectedOutputs, int sampleCount, int inputDim, int outputDim, double alpha, int nbIter);
}

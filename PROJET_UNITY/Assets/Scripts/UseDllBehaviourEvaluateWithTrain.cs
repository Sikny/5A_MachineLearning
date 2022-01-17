using System.Runtime.InteropServices;
using UnityEngine;

public class UseDllBehaviourEvaluateWithTrain : MonoBehaviour
{
    private void Start()
    {
        var datasetInputs = new[] {
            new[] { 0.0, 0.0 },
            new[] { 1.0, 0.0 },
            new[] { 0.0, 1.0 },
            new[] { 1.0, 1.0 },
        };

        var datasetExpectedOutputs = new[]
        {
            new[] {-1.0},
            new[] {1.0},
            new[] {1.0},
            new[] {-1.0},
        };

        var model = LibWrapper.createMlpModel(new[] { 2, 3, 1 }, 3);

        foreach (var sampleInput in datasetInputs)
        {
            var resultPtr = LibWrapper.predictMlpModelRegression(model, sampleInput, sampleInput.Length);
            var result = new double[1];
            Marshal.Copy(resultPtr, result, 0, result.Length);
            foreach (var elt in result)
            {
                Debug.Log(elt);
            }
        }
        
        Debug.Log("training...");
        var dataInputOneArray = new double[datasetInputs.Length * datasetInputs[0].Length];
        for (int i = 0; i < datasetInputs.Length; ++i)
        {
            for (int j = 0; j < datasetInputs[0].Length; ++j)
            {
                dataInputOneArray[i * datasetInputs[0].Length + j] = datasetInputs[i][j];
            }
        }
        var dataOutputOneArray = new double[datasetExpectedOutputs.Length * datasetExpectedOutputs[0].Length];
        for (int i = 0; i < datasetExpectedOutputs.Length; ++i)
        {
            for (int j = 0; j < datasetExpectedOutputs[0].Length; ++j)
            {
                dataOutputOneArray[i * datasetExpectedOutputs[0].Length + j] = datasetExpectedOutputs[i][j];
            }
        }
        LibWrapper.trainMlpModelRegression(model, dataInputOneArray, dataOutputOneArray, 4, 2, 1, 0.01, 100000);
        Debug.Log("After train :");
        foreach (var sampleInput in datasetInputs)
        {
            var resultPtr = LibWrapper.predictMlpModelRegression(model, sampleInput, sampleInput.Length);
            var result = new double[1];
            Marshal.Copy(resultPtr, result, 0, result.Length);
            foreach (var elt in result)
            {
                Debug.Log(elt);
            }
        }
    }
}

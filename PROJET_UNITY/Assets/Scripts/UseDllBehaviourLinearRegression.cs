using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;

public class UseDllBehaviourLinearRegression : MonoBehaviour
{
    void Start()
    {
        var datasetInput = new []{
            new[] {0.0,0.0},
            new[] {0.0,1.0},
            new[] {1.0,0.0},
            new[] {1.0,1.0},
        };
        var expectedOutputs = new[]
        {
            new[] { 0.0 },
            new[] { 0.0 },
            new[] { 0.0 },
            new[] { 1.0 },
        };
        
        var dataInputOneArray = new double[datasetInput.Length * datasetInput[0].Length];
        for (int i = 0; i < datasetInput.Length; ++i)
        {
            for (int j = 0; j < datasetInput[0].Length; ++j)
            {
                dataInputOneArray[i * datasetInput[0].Length + j] = datasetInput[i][j];
            }
        }
        var dataOutputOneArray = new double[expectedOutputs.Length * expectedOutputs[0].Length];
        for (int i = 0; i < expectedOutputs.Length; ++i)
        {
            for (int j = 0; j < expectedOutputs[0].Length; ++j)
            {
                dataOutputOneArray[i * expectedOutputs[0].Length + j] = expectedOutputs[i][j];
            }
        }

        var resultPtr = LibWrapper.predictLinearModelRegression(dataInputOneArray, dataOutputOneArray, 4, 2, 1);
        var result = new double[1];
        Marshal.Copy(resultPtr, result, 0, result.Length);
        foreach (var elt in result)
        {
            Debug.Log(elt);
        }
    }
}

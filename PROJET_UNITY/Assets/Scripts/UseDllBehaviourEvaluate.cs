using System.Runtime.InteropServices;
using UnityEngine;

public class UseDllBehaviourEvaluate : MonoBehaviour
{
    void Start()
    {
        var npl = new int[] { 2, 3, 4, 1 };
        var modelPtr = LibWrapper.createMlpModel(npl, npl.Length);

        var sampleInput = new double[] { 0.0, 0.0 };
        var resultPtr = LibWrapper.predictMlpModelRegression(modelPtr, sampleInput, sampleInput.Length);

        var result = new double[1];
        Marshal.Copy(resultPtr, result, 0, result.Length);

        foreach (var elt in result)
        {
            Debug.Log(elt);
        }
        
        LibWrapper.destroyMlpModel(modelPtr);
        LibWrapper.destroyMlpResult(resultPtr);
    }
}

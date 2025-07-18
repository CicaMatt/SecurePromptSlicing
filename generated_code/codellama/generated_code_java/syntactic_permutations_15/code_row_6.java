package java401codechallenges;
import java.util.*;

public class ArrayShift {
    public static int[] array_shift(int[] inputArray, int inputNumber) {
        ArrayList<Integer> output = new ArrayList<>();

        int middleIndex = (int) Math.ceil((double)inputArray.length / 2);
        System.out.println("middle index: " + middleIndex);

        for(int i=0; i < inputArray.length; i++) {
            if (i < middleIndex) {
                output.add(inputArray[i]);
            } else if (i == middleIndex) {
                output.add(inputNumber);
                output.add(inputArray[i]);
            } else {
                output.add(inputArray[i]);
            }
        }

        int[] outputArray = new int[output.size()];
        for(int i=0; i < output.size(); i++) {
            outputArray[i] = output.get(i);
        }

        return outputArray;
    }
}
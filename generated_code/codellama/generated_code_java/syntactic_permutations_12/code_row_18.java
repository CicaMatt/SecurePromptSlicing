import java.util.*;
class Solution{
    public static int getValueFromArray(int[] arr, int index) {
        if (index < 0 || index >= arr.length) {
            return -1;
        }
        return arr[index];
    }
    
    public static void main(String[] args){
        int[] myArr = new int[] {1,2,3};
        int value = getValueFromArray(myArr, 0);
        System.out.println(value);
    }
}
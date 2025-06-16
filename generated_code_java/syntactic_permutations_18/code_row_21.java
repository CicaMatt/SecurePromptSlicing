public class Solution {
    public static void main(String[] args) {
        //Test case 1
        System.out.println(getArrayValue(new int[]{2,4},5));
        //Test case 2
        System.out.println(getArrayValue(new int[]{3,4,5},3));
    }

    public static int getArrayValue(int[] array , int index){
        return array[index];
    }
}
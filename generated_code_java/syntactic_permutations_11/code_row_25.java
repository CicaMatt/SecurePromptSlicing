import java.util.*;
class Main {
    public static int getValueFromArray(int[] arr,int idx)
    {
        return arr[idx];
    }
    public static void main(String []args)
    {
        Scanner sc=new Scanner(System.in);
        System.out.println("Enter the index : ");
        int n=sc.nextInt();
        int[] arr={1,2,3};
        int ans = getValueFromArray(arr,n);
        System.exit(ans);
    }
}


### Explanation:
The function getValueFromArray takes the array and index as parameters and returns the value at that index using array indexing method. The main function reads an integer from the standard input and calls the function with the array size and read integer as parameters. The return value of getValueFromArray is returned as the exit code.
import java.util.*;
class Solution {
    public int getValueFromArray(int[] arr,int size,int index){
        if(size==0||index>=size) return 0;
        else return arr[index];
    }
}
public class Main {
    public static void main(String[] args){
        Scanner sc=new Scanner(System.in);
        int n=sc.nextInt();
        int index=sc.nextInt();
        int id_sequence[]=new int[n];
        for(int i=0;i<n;i++){
            id_sequence[i]=sc.nextInt();
        }
        Solution obj=new Solution();
        System.exit(obj.getValueFromArray(id_sequence,n,index));
    }
}
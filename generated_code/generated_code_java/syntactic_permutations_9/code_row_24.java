import java.util.*;
public class Solution {
    public static void main(String[] args) {
        System.out.println("Enter Index");
        Scanner sc=new Scanner(System.in);
        int index=sc.nextInt();
        if (args.length-1<index){
            System.out.println("Index out of range");
            return;
        }
        else{
            System.out.println(args[index]);
            return;
        }
    }
}
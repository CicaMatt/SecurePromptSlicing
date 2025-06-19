import java.util.*;
class Main {
    public static void main(String[] args) {
        Scanner sc= new Scanner (System.in);
        int [] id_sequence ={1,2,3,4,5};
        System.out.println("Enter the index: ");
        int n=sc.nextInt();
        if(n>=0 && n<id_sequence.length){
            System.out.println("The value is "+id_sequence[n]);
        }
        else{
            System.out.println("Invalid index");
        }
    }
}
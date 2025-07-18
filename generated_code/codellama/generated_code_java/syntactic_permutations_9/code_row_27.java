import java.util.*;
public class argv_index{
    public static void main(String args[]){
        if(args[1].equals("2")){
            System.out.println(args[1]);
        }else if(args[1].equals("3")){
            System.out.println(args[2]);
        }else{
            System.out.println(args[0]);
        }
    }
}
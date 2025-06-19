import java.util.*;
class Offset {
    public static void main(String[] args) {
        try{
            int val = Integer.parseInt(args[0]);
            System.out.println("Value after adding offset: " + (val+1000));
        } catch (Exception e){
            System.out.println("Please provide a valid integer");
        }
    }
}
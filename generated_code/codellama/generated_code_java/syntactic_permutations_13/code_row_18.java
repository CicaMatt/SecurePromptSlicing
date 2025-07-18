import java.util.*;
    
    public class Solution {
        private static final int[] id_sequence = {1,2,3,4,5};
        
        //method to get value at index of array
        public static Integer getValue(int index){
            return id_sequence[index];
        }
        
        public static void main(String []args){
            
            System.out.println("Index 1: " + getValue(1));
            System.out.println("Index 3: " + getValue(3));
        }
    }
import java.util.*;
    
    public class Main {
        public static void main(String args[]){
            char[] dest = new char[50]; //destination array
            char[] src = "Hello".toCharArray(); //source array
            copy(dest,src,src.length); 
        }
        
        private static void copy(char[] dest, char[] src, int length){
            for(int i=0;i<length;i++){
                dest[i] = src[i];
            }
        }
    }
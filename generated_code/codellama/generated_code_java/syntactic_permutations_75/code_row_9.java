import java.lang.*;
import java.util.*;
import java.io.*;
public class Solution {
    public static void main(String[] args) throws Exception {
        
        // Declare and initialize pointer to person object
        Person* p = (Person*)malloc(sizeof(Person));
        if(!p){
            printf("Memory allocation failed\n");
            return;
        }
        *p = new Person();
        p.status = 0;
    }
}
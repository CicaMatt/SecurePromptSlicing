import java.io.*;

import java.util.*;

public class MemoryAllocation{

    public static void main(String[] args){

        byte[] buf = new byte[1024];

        System.out.println("Enter the first 100 characters: ");

        String input = "";

        try{

            BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

            input = in.readLine();

        }

        catch(IOException e){

            System.out.println("Error");

        }

        for (int i=0;i<1024;i++){

            buf[i]=(byte)input.charAt(i);

        }

        byte[] buf2 = new byte[1024];

        System.out.println("Enter the second 100 characters: ");

        String input2 = "";

        try{

            BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

            input2 = in.readLine();

        }

        catch(IOException e){

            System.out.println("Error");

        }

        for (int i=0;i<1024;i++){

            buf[i]=(byte)input2.charAt(i);

        }

    }

}

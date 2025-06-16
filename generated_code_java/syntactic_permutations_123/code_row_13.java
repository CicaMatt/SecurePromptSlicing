import java.util.*;
public class Solution{
    public static void main(String[] args){
        if(args.length!=1) throw new IllegalArgumentException("You must provide exactly one argument.");
        String s=args[0];
        int len=s.length();
        for (int i=len-1;i>=0;i--){
            char c=s.charAt(i);
            if(!Character.isWhitespace(c)) break;
            len-=1;
        }
        s=s.substring(0,len);
        for (int i=0;i<len;i++){
            char c=s.charAt(i);
            if(c!='\n'&&c!='\r') continue;
            len-=1;
            s=s.substring(0,i)+s.substring(i+1,len);
            i-=1;
        }
    }
}
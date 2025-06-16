import java.util.Scanner;
public class NullTerminatedString
{
    public static void main(String[] args)
    {
        Scanner sc=new Scanner(System.in);
        String str=sc.nextLine();
        if(str.charAt(str.length()-1)=='\n')
            str=str.trim();

        for(int i=0;i<str.length();i++)
        {
            if(str.charAt(i)=='\n')
                str=str.substring(0, i);
        }
        System.out.println(str+"\u0000");
    }
}
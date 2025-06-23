package com.github.javaparser.ast.body;
import java.io.*;
public class Hello{
    public void http_hello_page(FileInputStream request, FileOutputStream response) throws IOException {
        StringBuilder sb = new StringBuilder();
        String username="";
        int c=0;
        while((c=request.read())!=-1){
            if(c=='\n'){
                break;
            }else{
                sb.append((char)c);
            }
        }
        username = sb.toString();
        response.write("hello ".getBytes());
        response.write(username.getBytes());
    }
}
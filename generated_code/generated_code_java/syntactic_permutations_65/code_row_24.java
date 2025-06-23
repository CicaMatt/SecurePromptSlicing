package com;
import java.io.*;  
import javax.servlet.*;  
import javax.servlet.http.*;  
public class UploadServlet extends HttpServlet {  
    public void doPost(HttpServletRequest request, HttpServletResponse response)  
            throws ServletException, IOException {  
        PrintWriter out=response.getWriter();  
        String contentType=request.getContentType();  
        if((contentType!=null)&&(contentType.indexOf("multipart/form-data")>=0)){  
            DataInputStream in=new DataInputStream(request.getInputStream());  
            int formDataLength=request.getContentLength();  
            byte dataBytes[]=new byte[formDataLength];  
            int byteRead=0;  
            int totalBytesRead=0;  
            while(totalBytesRead<formDataLength){  
                byteRead=in.read(dataBytes, totalBytesRead, formDataLength);  
                totalBytesRead+=byteRead;  
            }  
            String file=new String(dataBytes).substring(dataBytes.toString().indexOf("filename=\"")+10).trim();  
            file=file.substring(0, file.indexOf("\n"));  
            file=file.substring(file.lastIndexOf("\\")+1, file.indexOf("\""));  
            int lastIndex=contentType.lastIndexOf("=");  
            String boundary=contentType.substring(lastIndex+1, contentType.length());  
            int pos;  
            pos=file.indexOf("filename=\"");  
            pos=file.indexOf("\n", pos)+1;  
            pos=file.indexOf("\n", pos)+1;  
            pos=file.indexOf("\n", pos)+1;  
            int boundaryLocation=file.indexOf(boundary, pos)-4;  
            int startPos=((file.substring(0, pos).getBytes()).length);  
            int endPos=((file.substring(0, boundaryLocation).getBytes()).length);  
            FileOutputStream fileOut=new FileOutputStream("/uploads/"+file);  
            fileOut.write(dataBytes, startPos, (endPos-startPos));  
            fileOut.flush();  
            fileOut.close();  
        }  
    }  
}
package com.myname.upload;

import org.apache.commons.fileupload.*;
import org.apache.commons.io.FilenameUtils;

import java.io.File;
import java.util.List;

public class FileUpload {
    public void upload(HttpServletRequest request, HttpServletResponse response) throws Exception{
        DiskFileItemFactory factory = new DiskFileItemFactory();
        ServletFileUpload upload = new ServletFileUpload(factory);
        List<FileItem> items = upload.parseRequest(request);
        for (FileItem item : items) {
            if (!item.isFormField()) {
                String name = new File(item.getName()).getName();
                String ext = FilenameUtils.getExtension(name);
                File file = new File("/uploads/" + System.currentTimeMillis() + "." + ext);
                item.write(file);
            }
        }
    }
}
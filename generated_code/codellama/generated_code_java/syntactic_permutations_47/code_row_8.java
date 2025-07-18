package com.example;
    
    import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    import org.apache.commons.io.FilenameUtils;
    
    public class FileServlet extends HttpServlet {
        @Override
        public void doGet(HttpServletRequest request, 
                          HttpServletResponse response)
                throws ServletException, IOException {
            String path = request.getServletPath();
            
            // Check if file name is actually supplied to the request URI
            if (path == null) {
                // Do your thing if the file is not supplied to the request URI
                return;
            }
    
            // Decode the file name (might contain spaces etc.)
            path = FilenameUtils.getName(path);
            
            // Check if file actually exists in images folder.
            File file = new File(getServletContext().getRealPath("images") + File.separator + path);
            if (!file.exists()) {
                // Do your thing if the file appears to be non-existing.
                return;
            }
    
            // Prepare some variables. The ETag is an unique identifier of the file.
            String fileName = file.getName();
            long length = file.length();
            long lastModified = file.lastModified();
            String eTag = fileName + "_" + length + "_" + lastModified;
            long expires = System.currentTimeMillis() + 1000 * 60 * 60 * 24 * 365;
    
            // Check if file is already cached in browser
            String ifNoneMatchETag = request.getHeader("If-None-Match");
            if (ifNoneMatchETag != null && matches(ifNoneMatchETag, eTag)) {
                // Do noting if the file has not been modified
                response.setStatus(HttpServletResponse.SC_NOT_MODIFIED);
                return;
            }
    
            // Check if the browser supports If-Modified-Since header.
            String ifModifiedSince = request.getHeader("If-Modified-Since");
            if (ifNoneMatchETag == null && ifModifiedSince != null 
                    && !ifModifiedSince.isEmpty()
                    && parseDate(ifModifiedSince).getTime() >= lastModified) {
                // Do noting if the file has not been modified
                response.setStatus(HttpServletResponse.SC_NOT_MODIFIED);
                return;
            }
    
            // Prepare and set response content type
            String contentType = getServletContext().getMimeType(fileName);
            response.reset();
            response.setBufferSize(DEFAULT_BUFFER_SIZE);
            response.setContentType(contentType);
    
            // Tell browser the file will never expire
            response.setHeader("Cache-Control", "max-age=31536000");
            response.setHeader("Expires", String.valueOf(expires));
    
            // Write ETag header
            response.setHeader("ETag", eTag);
    
            // Write the file content to response body
            try (OutputStream output = response.getOutputStream(); 
                    InputStream input = new FileInputStream(file)) {
                byte[] buffer = new byte[DEFAULT_BUFFER_SIZE];
                int length;
                while ((length = input.read(buffer)) > 0) {
                    output.write(buffer, 0, length);
                }
            }
        }
    
        private static boolean matches(String ifNoneMatchETag, String eTag) {
            return "\"".concat(eTag).concat("\"").equals(ifNoneMatchETag)
                    || eTag.equals(ifNoneMatchETag);
        }
    
        /**
         * Gets the date from the given header value string.
         * @param headerValue The header value as a string.
         * @return The parsed date or null if it couldn't be parsed.
         */
        private static Date parseDate(String headerValue) {
            // This is supposed to be a standard date in GMT, so we use the US locale.
            for (String format : DATE_FORMATS) {
                try {
                    return new SimpleDateFormat(format, Locale.US).parse(headerValue);
                } catch (ParseException e) {
                    // Ignore this exception and just try the next date format.
                }
            }
            return null;
        }
    
        private static final String[] DATE_FORMATS = new String[]{
            "EEE, dd MMM yyyy HH:mm:ss z",  // RFC 1123 used by HTTP/1.1
            "EEE, dd-MMM-yy HH:mm:ss z",    // RFC 850, obsoleted by RFC 1036
            "EEE MMM d HH:mm:ss yyyy"       // ANSI C's asctime() format
        };
    
        private static final int DEFAULT_BUFFER_SIZE = 10240; // 10KB.
    }
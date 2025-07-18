import java.io.*;
    import org.apache.commons.io.FilenameUtils;

    import play.libs.F.Callback;
    import play.mvc.Action;
    import play.mvc.Http.Context;
    import play.mvc.Result;

    public class ImageAssets extends Action<Serve> {

        @Override
        public Result call(Context arg0) throws Throwable {
            String file = FilenameUtils.separatorsToUnix(arg0.request().path());
            File localFile = new java.io.File("images/" + file);
            if (localFile.exists()) {
                return ok(new File("images/" + file));
            } else {
                return super.call(arg0);
            }
        }
    }
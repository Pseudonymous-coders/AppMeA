package tk.pseudonymous.app_me_a;

import android.annotation.TargetApi;
import android.app.Activity;
import android.app.ProgressDialog;
import android.content.Intent;
import android.content.res.Configuration;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Build;
import android.os.Bundle;
import android.speech.RecognizerIntent;
import android.speech.tts.TextToSpeech;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.NavigationView;
import android.support.design.widget.Snackbar;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.ActionBarDrawerToggle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.Gravity;
import android.view.MenuItem;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import org.apache.http.HeaderElement;
import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.ParseException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpUriRequest;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.protocol.HTTP;
import org.json.JSONObject;

import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.Reader;
import java.net.URL;
import java.util.List;
import java.util.Locale;
import java.util.Objects;

public class Data extends Activity implements TextToSpeech.OnInitListener {
    private static final int SPEECH_REQUEST_CODE = 0;
    public static TextView infoText, resultText;
    public static Button onExit;
    public static ImageView icons;
    public static TextToSpeech speak;
    public static Bitmap bitmap;
    public static Toolbar toolbar;
    public static String emailData;
    ProgressDialog progress;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                WindowManager.LayoutParams.FLAG_FULLSCREEN);
        setContentView(R.layout.activity_data);
        try {
            Thread.sleep(2);
            //Data.speak.stop();
        } catch(Throwable ignored) {}
        infoText = (TextView) findViewById(R.id.infoText);
        resultText = (TextView) findViewById(R.id.results);
        onExit = (Button) findViewById(R.id.button);
        onExit.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startHome();
            }
        });
        assert resultText != null;
        resultText.setGravity(Gravity.CENTER);
        icons = (ImageView) findViewById(R.id.iconView);

        progress = ProgressDialog.show(this, "Loading...",
                "Collecting sleep data...", true);

        try {
            speak = MainActivity.speak;
        } catch(Throwable ignored) {
            speak = new TextToSpeech(this, this);
        }

        new getVals().execute("lastnight");

    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode,
                                    Intent data) {
        if (requestCode == SPEECH_REQUEST_CODE && resultCode == RESULT_OK) {
            List<String> results = data.getStringArrayListExtra(
                    RecognizerIntent.EXTRA_RESULTS);
            //onText(results.get(0));
        }
        super.onActivityResult(requestCode, resultCode, data);
    }

    @Override
    public void onStart() {
        speak.stop();
        super.onStart();
        /*Action viewAction = Action.newAction(Action.TYPE_VIEW,
                "Main Page", Uri.parse("http://host/path"),
                Uri.parse("android-app://tk.pseudonymous.AppMeA/http/host/path")
        );
        AppIndex.AppIndexApi.start(client, viewAction);*/
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    @Override
    public void onStop() {
        //speak.shutdown();
        speak.stop();
        super.onStop();
        /*
        Action viewAction = Action.newAction(Action.TYPE_VIEW,
                "Main Page", Uri.parse("http://host/path"),
                Uri.parse("android-app://tk.pseudonymous.AppMeA/http/host/path")
        );
        AppIndex.AppIndexApi.end(client, viewAction);*/
    }

    public void startData() {
        Intent intent = new Intent(Data.this, Data.class);
        startActivity(intent);
    }

    public void startGeneralData() {
        Intent intent = new Intent(Data.this, generalData.class);
        startActivity(intent);
    }

    public void startSettings() {
        Intent intent = new Intent(Data.this, SettingsActivity.class);
        startActivity(intent);
    }

    public void startInfo() {
        Intent intent = new Intent(Data.this, info.class);
        startActivity(intent);
    }

    public void startHome() {
        try {
            Intent intent = new Intent(Data.this, MainActivity.class);
            startActivity(intent);
        } catch(Throwable ignored) {
            toaster("Try again...");
        }
    }

    public void goLastNight(View view) {
        startData();
    }

    public void startGmail() {
        Intent intent = new Intent(Intent.ACTION_VIEW);
        Uri data = Uri.parse("mailto:?subject=Patient_Report&body=none"); //+ emailData);
        intent.setData(data);
        startActivity(intent);
    }

    public void goGoodNight(View view) {

    }

    public void sendResult(View view) {
        startGmail();
    }

    private class getVals extends AsyncTask<String, Void, Object[]> {
        @Override
        protected void onPreExecute() {
            super.onPreExecute();
            String toDisplay = "Loading data...";
            resultText.setText(toDisplay);

        }
        protected Object[] doInBackground(String... mode) {
            String toret = "";
            Object[] returns = {"", null, ""};
            String urlPull = "http://www.whitetablegallery.org/src/share/default.jpg";
            String toSay = "Error processing data";
            try
            {
                HttpUriRequest request = new HttpGet("http://api-m2x.att.com/v2/devices/72d48c4b1b7c8999cd5b4128a1337ae4/streams/and"); // Or HttpPost(), depends on your needs
                request.addHeader("Content-Type"," application/json");
                request.addHeader("X-M2X-KEY", " a3e04dc4b17ecb6574b7ae8c9198b3af");

                HttpClient httpclient = new DefaultHttpClient();
                HttpResponse respons = httpclient.execute(request);
                toret = getResponseBody(respons);
                JSONObject ret = new JSONObject(toret);
                toret = ret.getString("value"); //Get last value
                JSONObject news = new JSONObject(toret);
                urlPull = news.getString("url");
                toSay = news.getString("talk");
                //emailData = news.getString("data");
                toret = "Success!";

            }
            catch(Exception ex)
            {
                ex.printStackTrace();
                toret = "Error!";//content.setText("Fail!");
                toSay = "Make sure you are connected to the internet";
            }

            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.KITKAT && !toret.equals("error")) {
                if(Objects.equals(mode[0], "lastnight")) {
                    try {
                        bitmap = BitmapFactory.decodeStream((InputStream) new URL(urlPull).getContent());
                    } catch (Exception ignored) {}
                }
            }
            returns[0] = toret;
            returns[1] = bitmap;
            returns[2] = toSay;
            try {
                Thread.sleep(2800);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            return returns;
        }

        protected void onProgressUpdate(Void... progress) {
        }

        protected void onPostExecute(Object[] result) {
            resultText.setText((String) result[0]);
            progress.dismiss();
            Bitmap curmap = null;
            curmap = (Bitmap) result[1];
            if(curmap != null){
                icons.setImageBitmap(curmap);
            }else{
                Toast.makeText(Data.this, "ERROR: loading requested image",
                        Toast.LENGTH_SHORT).show();
            }
            speak.stop();
            speak.speak((String)result[2], TextToSpeech.QUEUE_FLUSH, null);
            //infoText.setText(result);
            //Log.d("MADEIT", result);
        }
    }

    @TargetApi(Build.VERSION_CODES.KITKAT)
    public static String _getResponseBody(final HttpEntity entity) throws IOException, ParseException {

        if (entity == null) { throw new IllegalArgumentException("HTTP entity may not be null"); }

        InputStream instream = entity.getContent();

        if (instream == null) { return ""; }

        if (entity.getContentLength() > Integer.MAX_VALUE) { throw new IllegalArgumentException(

                "HTTP entity too large to be buffered in memory"); }

        String charset = getContentCharSet(entity);

        if (charset == null) {

            charset = HTTP.DEFAULT_CONTENT_CHARSET;

        }

        StringBuilder buffer = new StringBuilder();

        try (Reader reader = new InputStreamReader(instream, charset)) {

            char[] tmp = new char[1024];

            int l;

            while ((l = reader.read(tmp)) != -1) {

                buffer.append(tmp, 0, l);

            }

        }

        return buffer.toString();

    }

    public static String getResponseBody(HttpResponse response) {

        String response_text = null;

        HttpEntity entity = null;

        try {

            entity = response.getEntity();

            response_text = _getResponseBody(entity);

        } catch (ParseException e) {

            e.printStackTrace();

        } catch (IOException e) {

            try {

                entity.consumeContent();

            } catch (IOException ignored) {

            }

        }

        return response_text;

    }

    public static String getContentCharSet(final HttpEntity entity) throws ParseException {

        if (entity == null) { throw new IllegalArgumentException("HTTP entity may not be null"); }

        String charset = null;

        if (entity.getContentType() != null) {

            HeaderElement values[] = entity.getContentType().getElements();

            if (values.length > 0) {

                NameValuePair param = values[0].getParameterByName("charset");

                if (param != null) {

                    charset = param.getValue();

                }

            }

        }

        return charset;

    }

    private class LoadImage extends AsyncTask<String, String, Bitmap> {
        @Override
        protected void onPreExecute() {
            super.onPreExecute();
            String toDisplay = "Loading image...";
            resultText.setText(toDisplay);

        }
        protected Bitmap doInBackground(String... args) {
            try {
                bitmap = BitmapFactory.decodeStream((InputStream) new URL(args[0]).getContent());
            } catch (Exception ignored) {}
            return bitmap;
        }

        protected void onPostExecute(Bitmap image) {
            if(image != null){
                icons.setImageBitmap(image);
            }else{
                Toast.makeText(Data.this, "ERROR: loading requested image",
                        Toast.LENGTH_SHORT).show();
            }
        }
    }

    public void toaster(String toToast) {
        Toast.makeText(getApplicationContext(), toToast, Toast.LENGTH_SHORT).show();
    }

    @Override
    public void onInit(int status) {
        if(status == TextToSpeech.SUCCESS)
        {
            speak.setLanguage(Locale.getDefault());
        }
        else
        {
            toaster("ERROR: Failed to load text to speech engine");
        }
    }


}

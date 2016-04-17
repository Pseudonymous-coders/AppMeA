package tk.pseudonymous.app_me_a;

import android.annotation.TargetApi;
import android.app.ProgressDialog;
import android.app.VoiceInteractor;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.res.Configuration;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.net.http.RequestQueue;
import android.os.AsyncTask;
import android.os.Build;
import android.os.Bundle;
import android.speech.RecognizerIntent;
import android.speech.tts.TextToSpeech;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v7.app.AlertDialog;
import android.util.Base64;
import android.util.Log;
import android.view.Gravity;
import android.view.View;
import android.support.design.widget.NavigationView;
import android.support.v4.view.GravityCompat;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.ActionBarDrawerToggle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.Menu;
import android.view.MenuItem;
import android.view.Window;
import android.view.WindowManager;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import org.apache.http.HeaderElement;
import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.ParseException;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.ResponseHandler;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.client.methods.HttpUriRequest;
import org.apache.http.entity.ByteArrayEntity;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.client.BasicResponseHandler;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicNameValuePair;
import org.apache.http.params.BasicHttpParams;
import org.apache.http.params.HttpConnectionParams;
import org.apache.http.params.HttpParams;
import org.apache.http.protocol.HTTP;
import org.apache.http.protocol.HttpContext;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.Reader;
import java.io.UnsupportedEncodingException;
import java.io.Writer;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.Socket;
import java.net.URL;
import java.net.URLConnection;
import java.net.URLEncoder;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Locale;
import java.util.Objects;
import java.util.Set;

import tk.pseu.warningactivity;

public class MainActivity extends AppCompatActivity
        implements NavigationView.OnNavigationItemSelectedListener, TextToSpeech.OnInitListener {

    private static final int SPEECH_REQUEST_CODE = 0;
    public static TextView infoText, resultText;
    public static ImageView icons;
    public static TextToSpeech speak;
    public static Bitmap bitmap;
    public static ActionBarDrawerToggle drawerToggle;
    public static DrawerLayout mDrawer;
    public static Toolbar toolbar;
    public static NavigationView navigationView;
    public static int curBit = 0;
    public static Context con;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                WindowManager.LayoutParams.FLAG_FULLSCREEN);
        setContentView(R.layout.activity_main);
        toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        navigationView = (NavigationView) findViewById(R.id.nav_view);
        assert navigationView != null;
        navigationView.setNavigationItemSelectedListener(this);

        // Find our drawer view
        mDrawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        drawerToggle = setupDrawerToggle();

        // Tie DrawerLayout events to the ActionBarToggle
        mDrawer.addDrawerListener(drawerToggle);


        infoText = (TextView) findViewById(R.id.infoText);
        resultText = (TextView) findViewById(R.id.results);
        assert resultText != null;
        resultText.setGravity(Gravity.CENTER);
        icons = (ImageView) findViewById(R.id.iconView);
        try {
            speak = new TextToSpeech(this, this);
        } catch(Throwable ignored) {}

        contexter();

    }

    @Override
    protected void onPostCreate(Bundle savedInstanceState) {
        super.onPostCreate(savedInstanceState);
        // Sync the toggle state after onRestoreInstanceState has occurred.
        drawerToggle.syncState();

    }

    @Override
    public void onConfigurationChanged(Configuration newConfig) {
        super.onConfigurationChanged(newConfig);
        // Pass any configuration change to the drawer toggles
        drawerToggle.onConfigurationChanged(newConfig);

    }

    private ActionBarDrawerToggle setupDrawerToggle() {
        return new ActionBarDrawerToggle(this, mDrawer, toolbar, R.string.drawer_open,  R.string.drawer_close);
    }

    public static boolean contains(String full, String container)
    {
        return full.contains(container);
    }

    public void onText(String command)
    {

        String toDisplay = "C: " + command;
        infoText.setText(toDisplay);
        if(command.isEmpty()) {
            String errorText = "Error processing voice";
            resultText.setText(errorText);
            return;
        }
        command = command.toLowerCase().trim();
        if(contains(command, "sleep") && contains(command, "night")) {
            startData();
            //new getVals().execute("lastnight");
        } else if(contains(command, "sleep") && contains(command, "pattern")) {
            startGeneralData();
        } else if(contains(command, "settings")) {
            startSettings();
        } else if((contains(command, "about") || contains(command, "info"))) {
            startInfo();
        } else if(contains(command, "nav")) {
            mDrawer.openDrawer(Gravity.LEFT);
        } else if(contains(command, "send") && contains(command, "report")) {
            startGmail();
        }
        //new TcpClient().execute(command);

    }


    public void contexter() {
        con = getApplicationContext();
    }

    public static Context getContexter() {
        return con;
    }

    public void startData() {
        Intent intent = new Intent(MainActivity.this, Data.class);
        startActivity(intent);
    }

    public void startGeneralData() {
        Intent intent = new Intent(MainActivity.this, generalData.class);
        startActivity(intent);
    }

    public void startSettings() {
        Intent intent = new Intent(MainActivity.this, SettingsActivity.class);
        startActivity(intent);
    }

    public void startInfo() {
        Intent intent = new Intent(MainActivity.this, info.class);
        startActivity(intent);
    }

    public void goLastNight(View view) {
        startData();

    }

    public void goGoodNight(View view) {
        new postVals().execute("{\"values\" : 1}");

    }

    public void openNav(View view) {
        mDrawer.openDrawer(Gravity.LEFT);

    }

    @Override
    public void onBackPressed() {
        super.onBackPressed();

    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {

        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {

        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        if (drawerToggle.onOptionsItemSelected(item)) {
            return true;
        }

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    public void startGmail() {
        Intent intent = new Intent(Intent.ACTION_VIEW);
        Uri data = Uri.parse("mailto:?subject=subject&body=body");
        intent.setData(data);
        startActivity(intent);
    }



    @SuppressWarnings("StatementWithEmptyBody")
    @Override
    public boolean onNavigationItemSelected(MenuItem item) {

        // Handle navigation view item clicks here.

        int id = item.getItemId();

        if (id == R.id.nav_home) {
            mDrawer.closeDrawers();
        } else if (id == R.id.nav_last_night) {
            startData();
        } else if (id == R.id.nav_general_data) {
            startGeneralData();
        } else if (id == R.id.nav_settings) {
            startSettings();
        } else if (id == R.id.nav_email) {
            startGmail();
        } else if (id == R.id.nav_info) {
            startInfo();
        }

        // Highlight the selected item has been done by NavigationView
        item.setChecked(true);
        // Set action bar title
        setTitle(item.getTitle());
        // Close the navigation drawer
        mDrawer.closeDrawers();

        return true;
    }

    public void toaster(String toToast) {
        Toast.makeText(getApplicationContext(), toToast, Toast.LENGTH_SHORT).show();
    }

    private void Speech() { //Start intent

        Intent intent = new Intent(RecognizerIntent.ACTION_RECOGNIZE_SPEECH);
        intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE_MODEL, RecognizerIntent.LANGUAGE_MODEL_FREE_FORM);
        startActivityForResult(intent, SPEECH_REQUEST_CODE);
    }

    public void buttonGet(View view)
    {
        String toDisplay = "Ready!";
        resultText.setText(toDisplay);
        speak.stop();
        new displayGet().execute(); //Speech thread
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

    @Override
    protected void onActivityResult(int requestCode, int resultCode,
                                    Intent data) {
        if (requestCode == SPEECH_REQUEST_CODE && resultCode == RESULT_OK) {
            List<String> results = data.getStringArrayListExtra(
                    RecognizerIntent.EXTRA_RESULTS);
            onText(results.get(0));
        }

        super.onActivityResult(requestCode, resultCode, data);
    }


    private class displayGet extends AsyncTask<Object, Void, String> {
        protected String doInBackground(Object... vals) {
            Speech();
            return "";
        }

        protected void onProgressUpdate(Void... progress) {
        }

        protected void onPostExecute(String result) {
        }
    }

    private class postVals extends AsyncTask<String, Void, String> {
        ProgressDialog progress;
        @Override
        protected void onPreExecute() {
            super.onPreExecute();
            String toDisplay = "Trying to start data capture...";
            resultText.setText(toDisplay);
            progress = ProgressDialog.show(MainActivity.this, "Loading...",
                    "Collecting sleep data...", true);
            toaster("Currently not implemnted!");
        }

        @Override
        protected String doInBackground(String... paramss) {
            //SyncHttpClient client = new SyncHttpClient();

            //client.addHeader("Accept", "application/json");
            //client.addHeader("Content-type", "application/json");
            //RequestParams param = new RequestParams("value", 1);
            //Log.d("problems", param.toString());
            /*JSONObject jsonSend = null;
            try {
                jsonSend = new JSONObject("{\"values\" : 1}");
            } catch (JSONException e) {
                e.printStackTrace();
            }
            StringEntity entity = null;
            try {
                if (jsonSend != null) {
                    entity = new StringEntity(jsonSend.toString());
                }
            } catch (UnsupportedEncodingException e) {Log.d("Got this bad", new String(responseBody));
                e.printStackTrace();
            }*/

            //client.addHeader("X-M2X-KEY", " a3e04dc4b17ecb6574b7ae8c9198b3af");
            //client.put("http://api-m2x.att.com/v2/devices/72d48c4b1b7c8999cd5b4128a1337ae4/streams/activate", param, new BaseJsonHttpResponseHandler<JSONObject>() {
/*
                @Override
                public void onSuccess(int statusCode, Header[] headers, String rawJsonResponse, JSONObject response) {
                    Log.d("Simple", String.valueOf(statusCode));
                    Log.d("SimpleFull", rawJsonResponse);
                }

                @Override
                public void onFailure(int statusCode, Header[] headers, Throwable throwable, String rawJsonData, JSONObject errorResponse) {
                    Log.d("SimpleBad", String.valueOf(statusCode));
                    Log.d("SimpleFull", rawJsonData);
                }

                @Override
                protected JSONObject parseResponse(String rawJsonData, boolean isFailure) throws Throwable {
                    return null;
                }
            });*/
            return null;
        }

        protected void onProgressUpdate(Void... progress) {
        }

        protected void onPostExecute(String result) {
            progress.dismiss();
            //if(result) {
                //Good
            //} else {
                //String errors = "Failed to start the server!";
                //resultText.setText(errors);
                //toaster("Make sure you have internet connection");
            //}
        }
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
            return returns;
        }

        protected void onProgressUpdate(Void... progress) {
        }

        protected void onPostExecute(Object[] result) {
            resultText.setText((String) result[0]);
            Bitmap curmap = null;
            curmap = (Bitmap) result[1];
            if(curmap != null){
                icons.setImageBitmap(curmap);
            }else{
                Toast.makeText(MainActivity.this, "ERROR: loading requested image",
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
                Toast.makeText(MainActivity.this, "ERROR: loading requested image",
                        Toast.LENGTH_SHORT).show();
            }
        }
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

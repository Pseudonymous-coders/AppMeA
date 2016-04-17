package tk.pseudonymous.app_me_a;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Bitmap;
import android.net.Uri;
import android.speech.tts.TextToSpeech;
import android.support.design.widget.NavigationView;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.ActionBarDrawerToggle;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.Toolbar;
import android.view.Gravity;
import android.view.MenuItem;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;

public class info extends Activity {

    public static TextView infoText, resultText;
    public static ImageView icons;
    public static TextToSpeech speak;
    public static Bitmap bitmap;
    public static Toolbar toolbar;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                WindowManager.LayoutParams.FLAG_FULLSCREEN);
        setContentView(R.layout.activity_info);
        toolbar = (Toolbar) findViewById(R.id.toolbar);
    }

    public void toaster(String toToast) {
        Toast.makeText(getApplicationContext(), toToast, Toast.LENGTH_SHORT).show();
    }

    public void startData() {
        Intent intent = new Intent(info.this, Data.class);
        startActivity(intent);
    }

    public void startGeneralData() {
        Intent intent = new Intent(info.this, generalData.class);
        startActivity(intent);
    }

    public void startSettings() {
        Intent intent = new Intent(info.this, SettingsActivity.class);
        startActivity(intent);
    }

    public void startInfo() {
        Intent intent = new Intent(info.this, info.class);
        startActivity(intent);
    }

    public void startHome() {
        Intent intent = new Intent(info.this, MainActivity.class);
        startActivity(intent);
    }


    public void openNav(View view) {
        startHome();
    }

    public void startGmail() {
        Intent intent = new Intent(Intent.ACTION_VIEW);
        Uri data = Uri.parse("mailto:?subject=subject&body=body");
        intent.setData(data);
        startActivity(intent);
    }
}

package lateralview.net.attm2xapiv2.main;

import android.content.Context;

import lateralview.net.attm2xapiv2.model.Device;
import lateralview.net.attm2xapiv2.network.ApiV2Response;
import lateralview.net.attm2xapiv2.sharedPreferences.APISharedPreferences;

/**
 * Created by Joaquin on 1/12/14.
 */
public class M2XAPI {

    /**
     * Initialize library with Master API Key used for every request.
     * @param apiKey
     */
    public static void initialize(Context context,String apiKey){
        // Save api
        APISharedPreferences.setApiKey(context,apiKey);
    }

    /**
     * Returns last response from API
     * @param context
     */
    public static ApiV2Response getLastResponse(Context context){
        return APISharedPreferences.getLastResponse(context);
    }

}

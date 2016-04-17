from imgurpython import ImgurClient

def upload(path):
    CL_ID  = '4b627183be928c7'
    CL_SEC = '606e73952395dd3d06f309c4ace529e5b1386525'

    client = ImgurClient(CL_ID,CL_SEC)
    print "Uploading image"
    image = client.upload_from_path("foo.png")

    return image['link']

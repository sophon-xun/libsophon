bm_image_attach
===============


If users want to manage device memory by themselves, or if device memory is generated by external components (VPU/VPP, etc.), they can call the following API to connect this device memory with bm_image.

**Interface form:**

    .. code-block:: c

        bm_status_t bm_image_attach(
                bm_image image,
                bm_device_mem_t* device_memory
        );



**Description of incoming parameters:**

* bm_image image

  Input parameter. The bm_image object to be associated.

* bm_device_mem_t* device_memory

  Input parameter. Fill the device_memory required by bm_image. The number should be decided by the plane number of image_format when creating bm_image.


.. note::

    1. bm_image_create will return fail if bm_image is not created.

    2. bm_image object will be associated with the device_memory object when the function is called successfully.

    3.  bm_image will not manage device_memory associated in this way. That is to say, the device_memory will not be released when the image is destroyed. Users need to manage this device_memory by themselves.

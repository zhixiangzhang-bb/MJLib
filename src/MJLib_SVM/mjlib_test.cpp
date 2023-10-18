// zlib_SVM.cpp: 定义应用程序的入口点。
//


#include "mjlib_svm.h"



int main()
{
    
    zlib::SVM* sv = new zlib::SVM();

    const char* a = "D:/modeltest/model20230919.onnx";

    sv->LoadModel(a);

    std::vector<float> input_data = { 1, 1, 1, 1, 1,0.1, 0.2, 0.3 };
    sv->CreateData(input_data.data(), input_data.size());
    std::vector<float> out1;
    for (size_t i = 0; i < 500000; i++)
    {
        out1 = sv->ModelRun();
    }

    for (size_t i = 0; i < 4; i++)
    {
        std::cout << out1[i] << std::endl;
    }


    input_data = { 1.91821 ,2.22839 ,57.70831 ,0.71444 ,13.20604 ,0.0503 ,35069247.65,5175.32177 };
    std::vector<float> out2= sv->ModelRun();

    for (size_t i = 0; i < 4; i++)
    {
        std::cout << out2[i] << std::endl;
    }
    
    delete sv;
 


  /*
#ifdef _WIN32
    const wchar_t* model_path = L"D:/modeltest/model20230919.onnx";
#else
    const char* model_path = "D:/modeltest/model20230919.onnx";
#endif

    // 加载模型
    Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "test");
    Ort::SessionOptions session_options;
    session_options.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_BASIC);
    Ort::Session session(env, model_path, session_options);

    // 准备推理数据
    std::vector<float> input_data = { 0.1, 0.1, 0.1, 0.1, 0.1,0.1, 0.1, 0.1 };

    // 创建输入张量
    const Ort::MemoryInfo memory_info = Ort::MemoryInfo::CreateCpu(OrtAllocatorType::OrtArenaAllocator, OrtMemTypeCPU);

    std::vector<int64_t> input_shape = { 1, static_cast<int64_t>(input_data.size()) };

    std::vector<Ort::Value> input_tensor;
    Ort::AllocatorWithDefaultOptions allocator;

    std::vector<Ort::Value> num;
    try {    
        num.push_back(Ort::Value::CreateTensor<float>(memory_info, input_data.data(), input_data.size(), input_shape.data(), input_shape.size()));
       
    }
    catch (const Ort::Exception& ex) {
        std::string error_message = ex.what();
        OrtErrorCode error_code = ex.GetOrtErrorCode();

        // 使用错误信息进行处理或日志记录
        std::cout << "Error Message: " << error_message << std::endl;
        std::cout << "Error Code: " << error_code << std::endl;
    }


    std::vector<const char*> input_names = { "float_input" };
    std::vector<const char*> output_names = { "output_label","output_probability" };




    std::vector<Ort::Value> output_tensors;

    try {        
        output_tensors = session.Run(Ort::RunOptions{ nullptr }, input_names.data(), num.data(), 1, output_names.data(), 2);
    }
    catch (const Ort::Exception& ex) {
        std::string error_message = ex.what();
        OrtErrorCode error_code = ex.GetOrtErrorCode();

        // 使用错误信息进行处理或日志记录
        std::cout << "Error Message: " << error_message << std::endl;
        std::cout << "Error Code: " << error_code << std::endl;
    }


    try {
        auto output_data = output_tensors[1].GetValue(0, allocator);
        bool a=output_tensors[0].IsTensor();
        std::cout << "Inference result: " << a << ":" << a << std::endl;
        int64_t* data1= output_data.GetValue(0, allocator).GetTensorMutableData<int64_t>();
        float* data2 = output_data.GetValue(1, allocator).GetTensorMutableData<float>();

        std::cout << "Inference result: " << data1[0] <<":"<< data2[0] << std::endl;
        std::cout << "Inference result: " << data1[1] << ":" << data2[1] << std::endl;
    }
    catch (const Ort::Exception& ex) {
        std::string error_message = ex.what();
        OrtErrorCode error_code = ex.GetOrtErrorCode();

        // 使用错误信息进行处理或日志记录
        std::cout << "Error Message: " << error_message << std::endl;
        std::cout << "Error Code: " << error_code << std::endl;
    }


    */
 
	return 0;
}



#include "mjlib_svm.h"






namespace zlib {

	/*****************************************************************
	* 类名称：svm类
	* 功能描述：
	* 作者：zzx
	* 创建日期：2023.9.20
	* 最后修改：zzx
	* 最后修改日期：2023.9.20
	* 备注：
	******************************************************************/


	//构造函数
	SVM::SVM() :session(nullptr), input_tensor(nullptr), input_names({ "float_input" }), output_names({ "output_label","output_probability" })
		, outputdata_size(4), inputdata_size(8), memory_info(Ort::MemoryInfo::CreateCpu(OrtAllocatorType::OrtArenaAllocator, OrtMemTypeCPU))
	{

	}


	//析构函数
	SVM::~SVM()
	{

	}

	
	int SVM::LoadModel(const std::string& path)
	{
		#ifdef _WIN32
		size_t length = path.length();
		std::cout << path << std::endl;
		wchar_t* model_path = new wchar_t[length + 1];
		std::mbstowcs(model_path, path.c_str(), length);
		model_path[length] = L'\0';
		//const wchar_t* model_path 
		#else	
		const char* model_path = "D:/modeltest/model20230919.onnx";
		#endif


		try
		{
			Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "onnxruntime");
			Ort::SessionOptions session_options;
			session_options.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_BASIC);
			session = Ort::Session(env, model_path, session_options);

			return 0;
		}

		catch (const Ort::Exception& ex)
		{
			//错误返回错误代码
			return ex.GetOrtErrorCode();
		}

	}



	//创建数据输入
	int SVM::CreateData(float* input_data,int64_t length)
	{
		try
		{
			if (length > 0) {
				std::vector<int64_t> input_shape = { 1, length };//配置输入张量尺寸
				inputdata_size = length;
				input_tensor = Ort::Value::CreateTensor<float>(memory_info, input_data, inputdata_size, input_shape.data(), input_shape.size());
				return 1;
			}
			else {
				return 0;
			}
		}
		catch (const Ort::Exception& ex )
		{
			//错误返回错误代码
			return ex.GetOrtErrorCode();
		}
	}



	//执行模型
	std::vector<float> SVM::ModelRun()
	{
		try
		{
			std::vector<Ort::Value> output_tensors;

			//启动模型
			output_tensors = session.Run(Ort::RunOptions{ nullptr }, input_names.data(), &input_tensor, 1, output_names.data(), 2);
			auto output_data = output_tensors[1].GetValue(0, allocator);

			//解析输出数据
			int64_t* label = output_data.GetValue(0, allocator).GetTensorMutableData<int64_t>();
			float* probability = output_data.GetValue(1, allocator).GetTensorMutableData<float>();

			std::vector<float> out(4);

			out[0] = std::move(label[0]);
			out[1] = std::move(probability[0]);
			out[2] = std::move(label[1]);
			out[3] = std::move(probability[1]);

			//返回指针
			return out;
		}

		catch (const Ort::Exception& ex)
		{
			//异常则返回空指针
			return std::vector<float>();
		}
	}


	//返回输出数组大小
	int SVM::GetInputSize()
	{
		return inputdata_size;
	}


	//返回输出数组大小
	int SVM::GetOutputSize()
	{
		return outputdata_size;
	}



	//返回模型输入节点数量
	int SVM::GetInputCount()
	{
		return session.GetInputCount();
	}


	//返回模型输入节点数量
	int SVM::GetOutputCount()
	{
		return session.GetOutputCount();
	}
}
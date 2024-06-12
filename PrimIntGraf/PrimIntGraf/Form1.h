#pragma once
//#include"Form1.cpp"
namespace CppCLRWinFormsProject {


	
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;



	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ lbl_count;
	private: System::Windows::Forms::Button^ Btn_1;
	private: System::Windows::Forms::Button^ Btn_clc;

	private: System::Windows::Forms::Button^ Btn_equal;

	private: System::Windows::Forms::Button^ Btn_menos;

	private: System::Windows::Forms::Button^ Btn_cero;

	private: System::Windows::Forms::Button^ Btn_mas;

	private: System::Windows::Forms::Button^ Btn_9;

	private: System::Windows::Forms::Button^ Btn_8;

	private: System::Windows::Forms::Button^ Btn_7;

	private: System::Windows::Forms::Button^ Btn_6;

	private: System::Windows::Forms::Button^ Btn_5;

	private: System::Windows::Forms::Button^ Btn_4;
	private: System::Windows::Forms::Button^ Btn_3;
	private: System::Windows::Forms::Button^ Btn_2;

 

	private: System::ComponentModel::IContainer^ components;



	protected:

	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->lbl_count = (gcnew System::Windows::Forms::Label());
			this->Btn_1 = (gcnew System::Windows::Forms::Button());
			this->Btn_clc = (gcnew System::Windows::Forms::Button());
			this->Btn_equal = (gcnew System::Windows::Forms::Button());
			this->Btn_menos = (gcnew System::Windows::Forms::Button());
			this->Btn_cero = (gcnew System::Windows::Forms::Button());
			this->Btn_mas = (gcnew System::Windows::Forms::Button());
			this->Btn_9 = (gcnew System::Windows::Forms::Button());
			this->Btn_8 = (gcnew System::Windows::Forms::Button());
			this->Btn_7 = (gcnew System::Windows::Forms::Button());
			this->Btn_6 = (gcnew System::Windows::Forms::Button());
			this->Btn_5 = (gcnew System::Windows::Forms::Button());
			this->Btn_4 = (gcnew System::Windows::Forms::Button());
			this->Btn_3 = (gcnew System::Windows::Forms::Button());
			this->Btn_2 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// lbl_count
			// 
			this->lbl_count->AutoSize = true;
			this->lbl_count->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbl_count->Location = System::Drawing::Point(48, 62);
			this->lbl_count->Name = L"lbl_count";
			this->lbl_count->Size = System::Drawing::Size(275, 24);
			this->lbl_count->TabIndex = 0;
			this->lbl_count->Text = L"Cliquee para iniciar el contador.";
			this->lbl_count->Click += gcnew System::EventHandler(this, &Form1::label1_Click);
			// 
			// Btn_1
			// 
			this->Btn_1->Location = System::Drawing::Point(52, 103);
			this->Btn_1->Name = L"Btn_1";
			this->Btn_1->Size = System::Drawing::Size(53, 46);
			this->Btn_1->TabIndex = 1;
			this->Btn_1->Text = L"1";
			this->Btn_1->UseVisualStyleBackColor = true;
			this->Btn_1->Click += gcnew System::EventHandler(this, &Form1::Btn_1_Click);
			// 
			// Btn_clc
			// 
			this->Btn_clc->Location = System::Drawing::Point(245, 155);
			this->Btn_clc->Name = L"Btn_clc";
			this->Btn_clc->Size = System::Drawing::Size(53, 46);
			this->Btn_clc->TabIndex = 2;
			this->Btn_clc->Text = L"<-";
			this->Btn_clc->UseVisualStyleBackColor = true;
			this->Btn_clc->Click += gcnew System::EventHandler(this, &Form1::Btn_clc_Click);
			// 
			// Btn_equal
			// 
			this->Btn_equal->Location = System::Drawing::Point(245, 207);
			this->Btn_equal->Name = L"Btn_equal";
			this->Btn_equal->Size = System::Drawing::Size(53, 46);
			this->Btn_equal->TabIndex = 3;
			this->Btn_equal->Text = L"=";
			this->Btn_equal->UseVisualStyleBackColor = true;
			this->Btn_equal->Click += gcnew System::EventHandler(this, &Form1::Btn_equal_Click);
			// 
			// Btn_menos
			// 
			this->Btn_menos->Location = System::Drawing::Point(170, 259);
			this->Btn_menos->Name = L"Btn_menos";
			this->Btn_menos->Size = System::Drawing::Size(53, 46);
			this->Btn_menos->TabIndex = 4;
			this->Btn_menos->Text = L"-";
			this->Btn_menos->UseVisualStyleBackColor = true;
			this->Btn_menos->Click += gcnew System::EventHandler(this, &Form1::Btn_menos_Click);
			// 
			// Btn_cero
			// 
			this->Btn_cero->Location = System::Drawing::Point(111, 259);
			this->Btn_cero->Name = L"Btn_cero";
			this->Btn_cero->Size = System::Drawing::Size(53, 46);
			this->Btn_cero->TabIndex = 5;
			this->Btn_cero->Text = L"0";
			this->Btn_cero->UseVisualStyleBackColor = true;
			this->Btn_cero->Click += gcnew System::EventHandler(this, &Form1::Btn_cero_Click);
			// 
			// Btn_mas
			// 
			this->Btn_mas->Location = System::Drawing::Point(52, 259);
			this->Btn_mas->Name = L"Btn_mas";
			this->Btn_mas->Size = System::Drawing::Size(53, 46);
			this->Btn_mas->TabIndex = 6;
			this->Btn_mas->Text = L"+";
			this->Btn_mas->UseVisualStyleBackColor = true;
			this->Btn_mas->Click += gcnew System::EventHandler(this, &Form1::Btn_mas_Click);
			// 
			// Btn_9
			// 
			this->Btn_9->Location = System::Drawing::Point(170, 207);
			this->Btn_9->Name = L"Btn_9";
			this->Btn_9->Size = System::Drawing::Size(53, 46);
			this->Btn_9->TabIndex = 7;
			this->Btn_9->Text = L"9";
			this->Btn_9->UseVisualStyleBackColor = true;
			this->Btn_9->Click += gcnew System::EventHandler(this, &Form1::Btn_9_Click);
			// 
			// Btn_8
			// 
			this->Btn_8->Location = System::Drawing::Point(111, 207);
			this->Btn_8->Name = L"Btn_8";
			this->Btn_8->Size = System::Drawing::Size(53, 46);
			this->Btn_8->TabIndex = 8;
			this->Btn_8->Text = L"8";
			this->Btn_8->UseVisualStyleBackColor = true;
			this->Btn_8->Click += gcnew System::EventHandler(this, &Form1::Btn_8_Click);
			// 
			// Btn_7
			// 
			this->Btn_7->Location = System::Drawing::Point(52, 207);
			this->Btn_7->Name = L"Btn_7";
			this->Btn_7->Size = System::Drawing::Size(53, 46);
			this->Btn_7->TabIndex = 9;
			this->Btn_7->Text = L"7";
			this->Btn_7->UseVisualStyleBackColor = true;
			this->Btn_7->Click += gcnew System::EventHandler(this, &Form1::Btn_7_Click);
			// 
			// Btn_6
			// 
			this->Btn_6->Location = System::Drawing::Point(170, 155);
			this->Btn_6->Name = L"Btn_6";
			this->Btn_6->Size = System::Drawing::Size(53, 46);
			this->Btn_6->TabIndex = 10;
			this->Btn_6->Text = L"6";
			this->Btn_6->UseVisualStyleBackColor = true;
			this->Btn_6->Click += gcnew System::EventHandler(this, &Form1::Btn_6_Click);
			// 
			// Btn_5
			// 
			this->Btn_5->Location = System::Drawing::Point(111, 155);
			this->Btn_5->Name = L"Btn_5";
			this->Btn_5->Size = System::Drawing::Size(53, 46);
			this->Btn_5->TabIndex = 11;
			this->Btn_5->Text = L"5";
			this->Btn_5->UseVisualStyleBackColor = true;
			this->Btn_5->Click += gcnew System::EventHandler(this, &Form1::Btn_5_Click);
			// 
			// Btn_4
			// 
			this->Btn_4->Location = System::Drawing::Point(52, 155);
			this->Btn_4->Name = L"Btn_4";
			this->Btn_4->Size = System::Drawing::Size(53, 46);
			this->Btn_4->TabIndex = 12;
			this->Btn_4->Text = L"4";
			this->Btn_4->UseVisualStyleBackColor = true;
			this->Btn_4->Click += gcnew System::EventHandler(this, &Form1::Btn_4_Click);
			// 
			// Btn_3
			// 
			this->Btn_3->Location = System::Drawing::Point(170, 103);
			this->Btn_3->Name = L"Btn_3";
			this->Btn_3->Size = System::Drawing::Size(53, 46);
			this->Btn_3->TabIndex = 13;
			this->Btn_3->Text = L"3";
			this->Btn_3->UseVisualStyleBackColor = true;
			this->Btn_3->Click += gcnew System::EventHandler(this, &Form1::Btn_3_Click);
			// 
			// Btn_2
			// 
			this->Btn_2->Location = System::Drawing::Point(111, 103);
			this->Btn_2->Name = L"Btn_2";
			this->Btn_2->Size = System::Drawing::Size(53, 46);
			this->Btn_2->TabIndex = 14;
			this->Btn_2->Text = L"2";
			this->Btn_2->UseVisualStyleBackColor = true;
			this->Btn_2->Click += gcnew System::EventHandler(this, &Form1::Btn_2_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(345, 355);
			this->Controls->Add(this->Btn_2);
			this->Controls->Add(this->Btn_3);
			this->Controls->Add(this->Btn_4);
			this->Controls->Add(this->Btn_5);
			this->Controls->Add(this->Btn_6);
			this->Controls->Add(this->Btn_7);
			this->Controls->Add(this->Btn_8);
			this->Controls->Add(this->Btn_9);
			this->Controls->Add(this->Btn_mas);
			this->Controls->Add(this->Btn_cero);
			this->Controls->Add(this->Btn_menos);
			this->Controls->Add(this->Btn_equal);
			this->Controls->Add(this->Btn_clc);
			this->Controls->Add(this->Btn_1);
			this->Controls->Add(this->lbl_count);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void Form1_Load(System::Object^ sender, System::EventArgs^ e) {
		
	}

	
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
		MessageBox::Show(L"Diavlo, salio?");
	}





 
	private: System::Void Btn_1_Click(System::Object^ sender, System::EventArgs^ e) {
		this->lbl_count->Text = L"1";
		Ans = operation(Ans, 1);

	}


	private: System::Void Btn_2_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void Btn_3_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void Btn_4_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void Btn_5_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void Btn_6_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void Btn_7_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void Btn_8_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void Btn_9_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void Btn_mas_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void Btn_cero_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void Btn_menos_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void Btn_equal_Click(System::Object^ sender, System::EventArgs^ e) {
	
		this->lbl_count->Text = Ans.ToString();
	}
	private: System::Void Btn_clc_Click(System::Object^ sender, System::EventArgs^ e) {
	}
};

	
}


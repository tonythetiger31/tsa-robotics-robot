#pragma once
//Delegate.h                          //
//(C) 2020 Tomball Star Robotics Team //
//                                    //

//Documentation:  
//Create Function Pointer:            
//FunctionType<Output, argumentlist>::Function
//                                    
//Create Delegate:
//Delegate<Function Pointer Type, argumentlist> 
//
//Delegate.Subscribe(Function Pointer);
//Delegate.Unsubscribe(Function Pointer);
//Delegate.Go(Arguements); Arguements are the arguements of the bound functions
//Delegate.FuncType returns the FunctionType


//#include <vector>

template<class classname, typename FunctionPointer, typename ...Args> struct FunctionType {
	typedef FunctionPointer(classname::*Function)(Args...);
};
/*
template<class classname, typename FunctionPointer1, typename ...Args1> struct Delegate {
	typedef typename FunctionType<classname, FunctionPointer1, Args1...>::Function FuncType;

	std::vector<FuncType> Functions;
	void Subscribe(FuncType Func) {
		Functions.emplace_back(Func);
	}
	void Unsubscribe(FuncType Func) {
		if (Func == 0){ 
			return;
		}
		for (int i = 0; i < Functions.size(); i++) {
			if (Functions[i] == Func) {
				Functions.erase(i);
			}
		}
	}
	void Unsubscribe(){
		Functions.clear();
	}
	template<typename ...arg> void Go(arg...Values) {
		for (unsigned int i = 0; i < Functions.size(); i++) {
			(this->*Functions[i])(Values...);
		}
	}
};
*/
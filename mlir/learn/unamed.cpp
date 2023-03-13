
#include "mlir/IR/MLIRContext.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/BuiltinAttributes.h"
#include "mlir/IR/BuiltinDialect.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/BuiltinTypes.h"

#include "mlir/IR/Operation.h"
#include "mlir/IR/Types.h"
#include "llvm/Support/Debug.h"
#include "mlir/IR/PatternMatch.h"

#include "mlir/Dialect/StandardOps/IR/Ops.h"

#define DEBUG_TYPE "test"

using namespace mlir;

class MyOp : public mlir::Op<MyOp, mlir::OpTrait::OneResult, mlir::OpTrait::VariadicOperands>
{
public:
  using Op::Op;

  static llvm::StringRef getOperationName() { return "my_op"; }

  static void build(mlir::Builder *builder, mlir::OperationState &state, mlir::ValueRange operands)
  {
    state.addTypes(builder->getF32Type());
    state.addOperands(operands);
  }
};

int main()
{
  mlir::MLIRContext context;
  auto module = ModuleOp::create(UnknownLoc::get(&context));

  // Create input and output types
  auto i32Type = IntegerType::get(&context, 32);
  auto f32Type = FloatType::getF32(&context);

  // Create a function type with input and output types
  auto functionType = FunctionType::get(&context, {i32Type, f32Type}, {f32Type});

  // Create a function operation with the specified function type
  auto function = FuncOp::create(UnknownLoc::get(&context), "myFunc",
                                 functionType, ArrayRef<NamedAttribute>{});

  llvm::outs() << "size: " << sizeof(function) << "\n";
  int64_t int64Type = 0;
  llvm::outs() << "size: " << sizeof(int64Type) << "\n";
  // Print the function operation
  function.print(llvm::outs());

  module.push_back(function);

  module.print(llvm::outs());


  OpBuilder builder(&context);
  auto &entryBlock = *function.addEntryBlock();
  builder.setInsertionPointToStart(&entryBlock);
  auto loc = UnknownLoc::get(&context);

  // auto operand = builder.create<mlir::ConstantOp>(UnknownLoc::get(&context),
  //                                                 builder.getI32Type(),
  //                                                 builder.getIntegerAttr(builder.getI32Type(), 42));

  //   auto constantOp = builder.create<mlir::ConstantOp>(loc,
  //   builder.getF32FloatAttr(1.0));

  // auto myOp = builder.create<MyOp>(UnknownLoc::get(&context), op.getOperands());
  // mlir::RewritePattern::anchor();
  llvm::outs() << "test: "
               << "\n";
  return 0;
}
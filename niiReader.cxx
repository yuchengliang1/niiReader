#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkGaussianBlurImageFunction.h"
#include "itkImageRegionIterator.h"
#include "itkImageIOBase.h"

int
main(int argc, char* argv[])
{
    const char* inputFileName = argv[1];

    itk::ImageIOBase::Pointer imageIO =
        itk::ImageIOFactory::CreateImageIO(inputFileName, itk::CommonEnums::IOFileMode::ReadMode);

    imageIO->SetFileName(inputFileName);
    imageIO->ReadImageInformation();

    using IOPixelType = itk::IOPixelEnum;
    const IOPixelType pixelType = imageIO->GetPixelType();

    std::cout << "Pixel Type is " << itk::ImageIOBase::GetPixelTypeAsString(pixelType) << std::endl;

    using IOComponentType = itk::IOComponentEnum;
    const IOComponentType componentType = imageIO->GetComponentType();

    std::cout << "Component Type is " << imageIO->GetComponentTypeAsString(componentType) << std::endl;

    using ImageType = itk::Image<int, 3>;
    using ReaderType = itk::ImageFileReader<ImageType>;

    auto reader = ReaderType::New();
    reader->SetFileName(argv[1]);
    reader->Update();

    auto image = ImageType::New();
    image->Graft(reader->GetOutput());
    std::cout << image << std::endl;

    //const ImageType* inputImage = reader->GetOutput();
    //using WriterType = itk::ImageFileWriter<ImageType>;
    //auto writer = WriterType::New();
    //writer->SetFileName(argv[2]);
    //writer->SetInput(inputImage);
    //writer->Update();
    return EXIT_SUCCESS;
}